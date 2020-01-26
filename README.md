# nl_rs

prebuild: sudo apt install libboost-dev

build: mkdir build && cd build && cmake .. && make

launch: rewriter file1.xml [fileN.xml]
