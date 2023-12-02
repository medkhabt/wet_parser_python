#! /bin/sh

../src/pavuk -verbose -dumpdir pavuk_data/ -noRobots -cdir pavuk_cache/ -cookie_send -cookie_recv -cookie_check -cookie_update -cookie_file pavuk_data/chunky-cookies3.txt -read_css -auto_referer -enable_js -info_dir pavuk_info/ -mode normal -index_name chunky-index.html -request "URL:http://www.hobbelt.com/ COOKIE:ird=123456789ABCDEF0;path=/" -scndir pavuk_scenarios/ -dumpscn TestScenario.txt -nthreads 1 -progress_mode 6 -referer -nodump_after -rtimeout 10000 -wtimeout 10000 -timeout 60000 -dumpcmd test_cmd_dumped.txt -debug -debug_level "all,!locks,!mtlock,trace,dev,!net,html,!procs,!mtthr,user,!hammer,protos,protoc,protod,bufio" -hammer_recdump @hammer_recording.txt -log_hammering -store_info -hammer_flags push_bogus -hammer_ease 2 -report_url_on_err -bad_content "Server is too busy,Service Unavailable" -tlogfile pavuk_log_timing.txt -dump_urlfd @pavuk_urlfd_dump.txt -dumpfd @pavuk_fd_dump.txt -dump_request -dump_response -logfile pavuk_log_all.txt -slogfile pavuk_log_short.txt -hammer_recdump @hammer_recording.txt -log_hammering -test_id T001 -formdata "URL:http://www.hobbelt.com/Pages/Account/Activate.aspx METHOD:POST FIELD:txtAlpha=otttest9" -formdata "URL:http://www.hobbelt.com/testform/ METHOD:POST FIELD:hdIRD= COOKIE:ird=123456789ABCDEF0" -formdata "URL:http://www.hobbelt.com/testform2/index.aspx METHOD:POST FIELD:hdIRD=" -adomain hobbelt.com
