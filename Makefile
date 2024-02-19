

# 1. Build the project
.PHONY: target
target: 
	  idf.py build;

# 2. Flash the project
.PHONY: flash
flash: 
	  idf.py -p /dev/ttyUSB0 flash  ;
# 2.1 Flash slow (115200)
.PHONY: flash-slow
flash-slow: 
	  idf.py -p /dev/ttyUSB0 flash -b 115200;
# 2.2 Flash fast (921600)
.PHONY: flash-fast
flash-fast: 
	  idf.py -p /dev/ttyUSB0 flash -b 921600;
# 3. Monitor the project
.PHONY: monitor
#monitor: 
#	  screen /dev/ttyUSB0 115200;
monitor:
	  idf.py -p /dev/ttyUSB0 flash monitor;

# 3. Clean the project
.PHONY: clean
clean: 
	  idf.py fullclean;


# 4. Test the project

.run_test:	
	  cd ./main/Components/build && make simple_test;

# 5. Build test env
# if the ./main/Components/build folder is not exist, create it
# and run cmake .. inside it
.build-test-env:
	  mkdir -p ./main/Components/build && cd ./main/Components/build && cmake ..;

# 6. create and run test env by running make build-test-env and run_test 
.PHONY: test
test: .build-test-env .run_test;


.PHONY: help
help: 
	  @echo "Usage: make [target]"
	  @echo "target:"
	  @echo "  target: build the project"
	  @echo "  flash: flash the project"
	  @echo "  flash-slow: flash the project with 115200 baudrate"
	  @echo "  flash-fast: flash the project with 921600 baudrate"
	  @echo "  monitor: monitor the project"
	  @echo "  clean: clean the project"
	  @echo "  test: test the project"
	  @echo "  help: show this help message and exit"