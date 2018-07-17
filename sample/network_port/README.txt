Payload SDK Network Port Function Sample.

====== The step to send test video ======

Step 1 : Config Linux Network IP.
Address : 192.168.5.3
Netmask : 255.255.255.0
Gateway : 192.168.5.1

Step 2 : build source file, use following cmd
cd source_code_dir
gcc testVideo.c -o testVideo

Step 3 : connect to payload sdk development board use network port.

Step 4 : run use following cmd
./testVideo

Step 5 : open psdk_demo.apk to see video

====== The step to send test data =======

Step 1 : Config Linux Network IP.
Address : 192.168.5.3
Netmask : 255.255.255.0
Gateway : 192.168.5.1

Step 2 : build source file, use following cmd
cd source_code_dir
gcc testDataTransfer.c -o testData

Step 3 : connect to payload sdk development board use network port.

Step 4 : run use following cmd
./testData

Step 5 : open psdk_demo.apk to see test data

