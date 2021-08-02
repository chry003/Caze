if [ ! -d "./src/" ]; then
	mkdir src
	mkdir src/classes
fi

if [ ! -d "./bin" ]; then
	mkdir bin
	mkdir bin/debug
	mkdir bin/release
	mkdir bin/target
	mkdir bin/target/exec
	mkdir bin/target/cple
fi

if [ ! -d "./include" ]; then
	mkdir include
	mkdir include/header
	mkdir include/lib
fi	

if [ ! -d "./test" ]; then
	mkdir test
fi

# copy all the classes file
dirs=(./src/classes/*/)

for dir in "${dirs[@]}"
do
	dirs2=($dir*/)

	for dir2 in "${dirs2[@]}"
	do
		if [ -d $dir2 ]; then
			cp $dir2* './bin/target/exec'
		fi
	done

	dirs3=($dir*)
	for dir3 in "${dirs3[@]}"
	do
		if [[ -f $dir3 ]]; then
			cp $dir3 './bin/target/exec'
		fi
	done
done

# copy main file
cp ./src/*.cpp "./bin/target/exec"

# build
g++ -c ./bin/target/exec/*.cpp ./bin/target/exec/*.c -std=c++14 -m64 -g -Wall -I include/header -I include/lib

# move compiled file
mv *.o './bin/target/cple'

# build all the obj file
g++ -g ./bin/target/cple/*.o -o bin/debug/main -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl

#remove old files
rm ./bin/target/exec/*
rm ./bin/target/cple/*

# Run
./bin/debug/main