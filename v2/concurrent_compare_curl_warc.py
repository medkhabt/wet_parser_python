#WARC Extraction
from fastwarc.warc import ArchiveIterator 
from fastwarc.stream_io import GZipStream


#Boilerplate removal
from resiliparse.extract.html2text import extract_plain_text

#Language identification
from resiliparse.parse.lang import detect_fast as d
import langid
import pycld2 as cld2  

#Util in Traitement
from bs4 import BeautifulSoup
import io
from os import path
import requests
import concurrent.futures
import sys
import json
# not used yet.
import time
import argparse

#LOCAL
import util

#PROFILING
import cProfile

def main(): 
    supported_lang_id_md = ['detect_fast','langid','cld2']
    parser = argparse.ArgumentParser(description='description about something') 
    parser.add_argument("--perf", help="calculate the time execution", action="store_true")
    parser.add_argument("--segement", "-s", help="warc segement to be treated", default="00000")
    parser.add_argument("--language_identifier", "-l", help="specify the language identification model, for now there are 3 that are supported ['detect_fast','langid','cld2']", default="detect_fast")  
    parser.add_argument("--number_records", "-n", type=int, help="the number of warc records that we are going to check", default=-1) 
    parser.add_argument("--timeout", "-t", type=float, help="the duration limit before the timeout", default=0.3) 
    parser.add_argument("--workers", "-w", type=int, help="The number of max number of workers in the thread pool.", default=100)

    args = parser.parse_args()
    perf_calc = True if args.perf else False ; 
    seg_number = args.segement
    size = args.number_records
    lang_id_model = args.language_identifier;
    timeout = args.timeout;
    n_workers= args.workers;
    if(lang_id_model not in supported_lang_id_md): 
        print("you chose an unsupported language identification model") 
        print("We are defaulting to 'detect_fast'")
        lang_id_model = 'detect_fast'
    print(f"args are : [ perf_calc : {perf_calc} , seg_number = {seg_number}, language_identification model : {lang_id_model}, number of record = {size}  timeout: {timeout}, number of workers: {n_workers}]")
    warc_url = f'https://data.commoncrawl.org/crawl-data/CC-MAIN-2023-40/segments/1695233505362.29/warc/CC-MAIN-20230921073711-20230921103711-{seg_number}.warc.gz'
    bundle = [];
    res = requests.get(warc_url); 
    if res.status_code == 200: 
        print(f'Downloaded: {str(warc_url)}')
        save_cc(res, lang_id_model, perf=perf_calc, seg_number = seg_number, size=size, timeout=timeout, n_workers=n_workers)
    else :
        print("Failed")
def decode(record, charset: str): 
    """ Decoding the content of the record 'Strategy'"""
    default_encoding = 'iso-8859-1';
    try:
        record_content = record.reader.read().decode(charset)
        if  record_content == None: 
            return 1; 
        return record_content;
    except UnicodeDecodeError :
        if charset == default_encoding:
            return 1;
        elif charset == 'utf-8' or charset == None or  record.http_charset == 'utf-7': 
            return decode(record, default_encoding); 
        elif charset == 'gbk' : 
# source https://stackoverflow.com/questions/3218014/unicodeencodeerror-gbk-codec-cant-encode-character-illegal-multibyte-sequen 
            return decode(record, 'gb18030')
        elif charset == 'shift_jis': 
# source https://stackoverflow.com/questions/6729016/decoding-shift-jis-illegal-multibyte-sequence
            return decode(record, 'shift_jisx0213')
        elif charset == 'euc-jp': 
# source https://stackoverflow.com/questions/73255012/python-fails-to-decode-euc-jp-strings-with-the-character 
            return decode(record, 'euc-jisx0213');
        elif charset == 'windows-1251': 
            return decode(record, 'utf-8')
        else: 
            return 1;
	
     
def save_cc(res, language_identification_model, seg_number='00000', perf=0 ,offset=0, size=1000000, timeout=1, n_workers=100):
    """
    Process the record list and transform to some log files.

    Gets the response of the downloaded segement content, delegate the information retrieval to fill_dataset and save the information in log files. 

    Parameters
    ----------
    res: requests.Response 
        We are going to use the Byte content of the response object that we got from the url fo the segement. 
    language_identification_model: str @TODO maybe we should use enums
        The language identification model that will be used to identify the language of the content of the page. 
    seg_number: str
        Segement number of the downloaded content, used to name the log files.  
    perf: 
    """
    dataset = [] 
    counter = 0;
    counters = {"timeout_err_ct" : 0, 
		"http_err_ct" : 0,
		"conn_err_ct" : 0}
    enc_pr_ctr = 0;
    res_bytesio = io.BytesIO(res.content)
    res_stream = GZipStream(res_bytesio)
    dataset = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=150) as executor:
        future_urls = [] 
        for record in ArchiveIterator(res_bytesio):
            if counter < offset : 
                continue; 
            if size >= 0 and counter >= size :
                break;
            if record.http_charset == None or  record.http_charset == 'utf-7': 
                charset = 'utf-8'
                #print(f'default to utf-8')
            else:
                charset = record.http_charset
                #print(f'we have a charset info which is {charset}')                   
            res = decode(record, charset)
            if res == 1 : 
# TODO Probably add a log to the urls that couldn't get decoded.
                enc_pr_ctr = enc_pr_ctr + 1;
                continue;
# TODO don't really need the else
            else: 
                future_urls.append(executor.submit(fill_dataset, record, res, language_identification_model, counters, timeout))
            for future in concurrent.futures.as_completed(future_urls):
                try:
                    data = future.result();
                    if(data != 1) : 
                        dataset.append(data)
                except Exception as e: 
                    print("future exception: {e}")
#                fill_dataset(dataset, record, res, language_identification_model, counters, timeout)
                        #    print(f'*********\n header items are : {record.http_headers.items()}')
            counter = counter + 1
            print(f"--record traited count : {counter} out of {'max' if size < 0 else size}")
# For the second try we just break and ignore that link
    res_bytesio.close()
    print(f' We had {enc_pr_ctr} enconding instance problem out of {counter}') 
    print(f"timeout_err_ct : {counters['timeout_err_ct']}, http_err_ct: {counters['http_err_ct']}, conn_err_ct: {counters['conn_err_ct']}")
#TODO all of this part is hardcoded for now, in case we want to experiment with other language identfication models we need to refactor this for a smoother experience :D 

    with open(f'logs/comp_{seg_number}.log', 'w', encoding='utf-8') as f: 
# Found a problem with the max caraters allowed in a single line, the process get killed.
#        json.dump(dataset, f, ensure_ascii = False, indent=2)
        f.write(f"meta_warc|http_header_warc|lang_warc|meta_curl|http_header_curl|lang_curl\n")
        for dr in dataset  :
            f.write(f"{dr['warc']['meta']}|{dr['warc']['http_header']}|{dr['warc']['lang']['lang']}|{dr['curl']['meta']}|{dr['curl']['http_header']}|{dr['curl']['lang']['lang']}\n")



def fill_dataset(record, content, language_identification_model, counters, timeout):
####### WARC PART
    # META LANGUAGE INFO  
    res = {'warc' : {}, 'curl': {}} 
    meta_language = util.get_meta_language(content)
    # HTTP LANGUAGE HEADER 
#TODO change the way to get the langugae header so we can refactor this part when curling .
    http_language_header = util.get_http_language_header_warc(record); 
    lg_id_warc = util.language_identification(util.boilerplate_removal(content), language_identification_model) 
    res['warc'] =  {
	    'uri' : record.headers.get('WARC-Target-URI'),
	    'id' : record.headers.get('WARC-Record-ID'),
	    'len' : record.headers.get('Content-Length'),
	    'http_header' : http_language_header if http_language_header is not None else '-',
	    'meta' : meta_language if meta_language is not None else '-',
            'lang' : {'lang':'un', 'precision' : 0} if lg_id_warc == 1 or lg_id_warc['lang'] == 'unknown' or len(lg_id_warc) > 2 else  lg_id_warc

}
######## CURL PART
    ## curl the uri 
    warc_dic = res['warc']
    if warc_dic['uri'] is None:
        return 1
#    print(f"the info of the warc file is {res['warc']}")
    try: 
#        headers = {"Accept-Language": "en-US, en; q=0.5"}
        headers = {"Accept-Language": None}
        r = requests.get(res['warc']['uri'], headers=headers, timeout=timeout)
    except requests.exceptions.ConnectTimeout as e: 
        counters['timeout_err_ct'] = counters['timeout_err_ct'] + 1
        return 1 
    except requests.exceptions.HTTPError as e: 
        counters['http_err_ct'] = counters['http_err_ct'] + 1
        return 1 
    except requests.exceptions.ConnectionError as e: 
        counters['conn_err_ct'] = counters['conn_err_ct'] + 1
        return 1 
    except Exception as e: 
#        print(e)
        return 1; 
    content = r.text
    http_content_header = util.get_http_language_header_curl(r)
    lg_id_curl = util.language_identification(util.boilerplate_removal(content), language_identification_model) 
    res['curl'] = {
         'http_header': headers["Accept-Language"] if headers["Accept-Language"] is not None else '-',
         'http_content_header' : http_content_header if http_content_header is not None else '-' , 
         'meta':  util.get_meta_language(content), 
         'lang':  {'lang':'un', 'precision' : 0} if lg_id_curl == 1 or lg_id_curl['lang'] == 'unknown' or len(lg_id_curl) > 2 else  lg_id_curl
 
    } 
#    print(f"r['headers'] = {r.headers}")
#    print(f"res['curl'] = {res['curl']}")
## detect_fast uses unknown instead of un.


    return res
main()
