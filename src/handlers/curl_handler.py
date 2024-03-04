from handlers.handler_basis import AbstractHandler
from typing import Any, Optional
import requests
import logging
class CurlHandler(AbstractHandler): 
    def __init__(self, headers=None, proxies=None): 
        self._headers = headers  
        self._proxies = proxies
    def handle(self, request:Any) -> Optional[Any] : 
    ## check if there is any uri 
        if 'uri' in request: 
            try: 
                if request['uri'] is None:
                   logging.warning("skipped")
                   return 1 
                timeout = request['timeout'] if 'timeout' in request else 3
#185.199.229.156:7492:jtxlsruj:36hyaqrdp9jm , Spain (Madrid) 

                proxies = {'https':"http://jtxlsruj:36hyaqrdp9jm@185.199.229.156:7492", 'http': "http://jtxlsruj:36hyaqrdp9jm@185.199.229.156:7492"} 
                r = requests.get(request['uri'], headers=self._headers, proxies=self._proxies, timeout=timeout) 
                request['content'] = r.text
                request['record'] = r
                request['type-content'] = 'local'
                return super().handle(request);
            except requests.exceptions.ConnectTimeout as e: 
                return 1 
            except requests.exceptions.HTTPError as e: 
                return 1 
            except requests.exceptions.ConnectionError as e: 
                return 1 
            except Exception as e: 
                return 1 
        else: 
            # TODO Refactor the handle of missing args for the handlers.
            raise Exception("Couldn't find one/some/all of the following keys ['uri'] in the request dict") 