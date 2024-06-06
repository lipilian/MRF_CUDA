CXX = g++
CXXFLAGS = -std=c++17 -fopenmp `pkg-config --cflags opencv4`
LDLIBS = `pkg-config --libs opencv4`

brutalforce: brutal_force.cpp
	$(CXX) $(CXXFLAGS) -o brutalforce brutal_force.cpp $(LDLIBS)

openmp: openmp.cpp
	$(CXX) $(CXXFLAGS) -o openmp openmp.cpp $(LDLIBS)

cuda: opencvcuda.cpp
	g++ -I /usr/local/include/opencv4/ -L /usr/local/lib/ opencvcuda.cpp -o output -lopencv_core -lopencv_imgcodecs -lopencv_cudastereo

run_brutalforce: brutalforce
	./brutalforce

run_openmp: openmp
	./openmp

clean:
	rm -f brutalforce openmp




