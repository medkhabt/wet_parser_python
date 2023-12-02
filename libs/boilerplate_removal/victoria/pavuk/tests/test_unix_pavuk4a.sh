#! /bin/sh

../src/pavuk -ignore_chunk_bug -verbose -dumpdir pavuk_data/ -noRobots -cdir pavuk_cache/ -singlepage -read_css -auto_referer -info_dir pavuk_info/ -mode normal -index_name chunky-index.html -request "URL:http://www.fanlib.ru/GetBook.ashx?type=html&Id=a40e7088-40a5-4c03-8b97-2bde224b7b72&UserId=00000000-0000-0000-0000-000000000000" -scndir pavuk_scenarios/ -dumpscn TestScenario4b.txt -nthreads 1 -progress_mode 6 -referer -nodump_after -rtimeout 10000 -wtimeout 10000 -timeout 60000 -dumpcmd test_cmd_dumped.txt -debug -debug_level "all,!locks,!mtlock,trace,dev,!net,html,!procs,!mtthr,user,protos,protoc,protod,bufio" -store_info -report_url_on_err -tlogfile pavuk_log_timing.txt -dump_urlfd @pavuk_urlfd_dump.txt -dumpfd @pavuk_fd_dump.txt -dump_request -dump_response -logfile pavuk_log_all.txt -slogfile pavuk_log_short.txt -test_id T004 
