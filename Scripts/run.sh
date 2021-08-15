cp "./build/Caze" "./bin"

rm ./build/Caze

cmake -B ./build -DCMAKE_BUILD_TYPE=Release

cmake --build ./build --config Release

if [[ -f "./build/Caze" ]]; then
	./build/Caze
fi