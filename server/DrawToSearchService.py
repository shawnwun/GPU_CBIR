#!/usr/bin/python
# -*- coding: utf-8 -*
import sys
import os
import re
#dirname = os.path.dirname(os.path.realpath(__file__))
#sys.path.insert(0, dirname+'/../util/')
#sys.path.insert(0, dirname+'/../classifier/')

import mechanize
import cookielib
import json
import urllib
import traceback                                                              
from gevent import pywsgi
from Search import *


indexing = None

def search(request, response):
    
    # parse parameters
    query_str = request['QUERY_STRING']
    var = {}
    for param_str in query_str.split('&'):
        params = param_str.split('=')
        var[params[0]] = params[1]
    
    # ranking
    if var.has_key('img'):
	feature = process_img(var.has_key('img'))
	rank_list = rank(feature,indexing)
	return rank_list
    else:
	return None

REQUEST_HANDLERS = {'GET':{}, 'POST':{}}
def register_handler(request_method, route_path, func):
    REQUEST_HANDLERS[request_method][route_path] = func

def router(request, response):
    try:
        path = request['PATH_INFO']
        method = request['REQUEST_METHOD']
        result = REQUEST_HANDLERS[method][path](request, response)
        response('200 OK', [('Content-Type', 'text/json')])
        return json.dumps({'status_code': 0, 'result': result})
    except KeyError:
        response('404 Not Found', [('Content-Type', 'text/json')])
        return json.dumps({'status_code': 1, 'result': []})

def run_service_as_rest_server(port):
    register_handler('GET', '/search', search)
    try:
        server = pywsgi.WSGIServer(('', port), router)
        print "Category API server is running at port(%s)"%port
        server.serve_forever()
    except KeyboardInterrupt:
        # shutdown xmlrpc server correctly
        print "Shutdown successfully!"
    except:
        # abnormal shutdown
        error = traceback.format_exc()
        print error

if  __name__ == "__main__":

    indexing = load_model()
    if sys.argv[1:]:
        port = int(sys.argv[1])
    else:
        port = 8801
    try:
        run_service_as_rest_server(port)
    except:
        print traceback.format_exc()
        print "Exception!!!!!!"

