#WARC Extraction
from fastwarc.warc import ArchiveIterator 
from fastwarc.stream_io import GZipStream
import requests
import sys
import io
# not used yet.



from handlers.decoding_handler import DecodingHandler 
from handlers.boiler_plate_handler import BoilerPlateHandler 
from handlers.extraction_handler import ExtractionHandler 
from handlers.language_identification_handler import LanguageIdentificationHandler 
from handlers.stats_handler import StatsHandler 
from handlers.repo_handler import RepoHandler 


#def save_cc(res, seg_number='00000', perf=0 ,offset=0, size=100000):
def compare_language_identification_models_pipeline(record, language_models) : 
# Create instances of the necessary handlers for our pipeline.
# decode => boilerplate => extraction => language_identificaiton => stats => repo.
    decoding = DecodingHandler(); 
    boilerplate = BoilerPlateHandler(); 
    extraction = ExtractionHandler(); 
    language_identification = LanguageIdentificationHandler(); 
    stats = StatsHandler(); 
    repo = RepoHandler(100); 
    

    decoding.set_next(boilerplate).set_next(extraction).set_next(language_identification).set_next(stats).set_next(repo)
    request = {
	'record' : record, 
        'language_models': language_models 
}
    decoding.handle(request)
def pre_traitement_seg_data(res): 
    return GZipStream(io.BytesIO(res.content))

if __name__ == "__main__" : 

# pre-traitement and initialization before the execution of the pipleline. 

    if len(sys.argv) > 1: 
        perf_calc = 1 if sys.argv[1] == '1' else 0;
    else: 
        perf_calc = 0 
    if len(sys.argv) > 2 and len(sys.argv[2]) == 5 : 
        seg_number = sys.argv[2]
    else: 
        seg_number = '00000'
    print(f"args are : [ perf_calc : {perf_calc} , seg_number = {seg_number} ]")
    warc_url = f'https://data.commoncrawl.org/crawl-data/CC-MAIN-2023-40/segments/1695233505362.29/warc/CC-MAIN-20230921073711-20230921103711-{seg_number}.warc.gz'
    bundle = [];
    res = requests.get(warc_url); 
    counter = 0;
    enc_pr_ctr = 0;
    dataset = []
    size = 1000
    #accuracy = {'size': 0, 'match' : 0, 'detect_fast' : {'wrong' : 0 , 'uniq' : 0}, 'langid' : {'wrong' : 0 , 'uniq' : 0}, 'cld2' : {'wrong' : 0 , 'uniq' : 0}}
    #unknowns_dic = {'detect_fast' : 0, 'langid' : 0, 'cld2' : 0}
    perf_dict = {'perf' : perf_calc, 'detect_fast' : 0, 'langid' : 0, 'cld2' : 0}

# TODO this also shoudl be a param
    language_identification_models = ['detect_fast', 'langid', 'cld2'] 
    if res.status_code == 200: 
        print(f'Downloaded: {str(warc_url)}')
        for record in ArchiveIterator(pre_traitement_seg_data(res)):
            if counter >= size :
                break;
            compare_language_identification_models_pipeline(record, language_identification_models)
# TODO Probably add a log to the urls that couldn't get decoded.
# TODO don't really need the else
        fill_dataset(dataset, record, res,accuracy,unknowns_dic, perf_dict)

        save_cc(res, perf=perf_calc, seg_number = seg_number)
    else :
        print("Failed")

## it is going to contain the argument extraction part. 

