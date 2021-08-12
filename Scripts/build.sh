touch ./build/log/log.txt

mode=""

declare -A color
color[red]=31
color[green]=32
color[yellow]=33
color[blue]=34
color[white]=37

# boldness color text
function bnr()
{
	echo -e "\e[$1;$2m$3\e[0m"
}

# status
function headerStart()
{
	echo ""
	path=$(pwd)
	echo "[$(bnr 1 ${color[yellow]} "MODE"): $(bnr 1 ${color[white]} ${mode})][$(bnr 1 ${color[yellow]} "STATUS"): $(bnr 1 ${color[white]} "$1")][$(bnr 1 ${color[yellow]} "PATH"): $(bnr 1 ${color[white]} ${path})]"
	echo ""
}

function info()
{
	echo "[$(bnr 1 ${color[green]} "*")] $(bnr 1 ${color[white]} "$1")"
	sleep 0.3
}

function errorInfo()
{
	echo "[$(bnr 1 ${color[red]} "*")] $(bnr 1 ${color[red]} "Error While Compiling")"
	echo ""
	echo "$(bnr 1 ${color[yellow]} "$1")"
	echo ""
	echo "[$(bnr 1 ${color[red]} "*")] $(bnr 1 ${color[yellow]} "Do you want to continue?")" && read out
	if [[ $out == n ]]; then
		exit
	fi
}

function headerEnd()
{
	clear
}

function createandcopy()
{
	headerStart "Creating Files"

	dirs=(./Caze-Core/src/*/)

	for dir in "${dirs[@]}"
	do
		info "$dir"

		dirs2=($dir*/)

		for dir2 in "${dirs2[@]}"
		do
			info "$dir2"
			if [ -d $dir2 ]; then
				cp $dir2* './build/target/'
			fi
		done

		dirs3=($dir*)
		for dir3 in "${dirs3[@]}"
		do
			info "$dir3"
			if [[ -f $dir3 ]]; then
				cp $dir3 './build/target/'
			fi
		done
	done
	headerEnd

	# copy main file
	headerStart "Source Code"
	info "$(ls ./Caze-Core/*.cpp)"
	cp ./Caze-Core/*.cpp './build/target/'
	headerEnd

}

function removeandmove()
{
	# move compiled file
	headerStart "Removing and Moving compiled files!"
	rm ./build/target/*
	mv *.o './build/target/'
	info "rm ./build/target/*"
	info "mv *.o './build/target/'"
	headerEnd
}

if [[ $1 == debug ]]; then

	mode="DEBUG"

	createandcopy

	# build
	headerStart "Compiling Source Code"
	g++ -c ./build/target/*.cpp ./build/target/*.c -std=c++14 -m64 -g -Wall -I include/Caze -I include/vendor &> ./build/log/log.txt

	if [ -s ./build/log/log.txt ]; then
		headerEnd

		headerStart "Error"
		errorInfo "$(cat ./build/log/log.txt)"
	fi

	compiledFiles=(./*.o)
	for files in "${compiledFiles[@]}"
	do
		info "${files}"
	done
	headerEnd

	removeandmove

	# build all the obj file
	headerStart "Building compiled files"
	g++ -g ./build/target/*.o -o build/bin/debug/Caze-Core -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl
	info "Caze-Core"
	headerEnd

	if [ ! -d "build/bin/debug/include" ]; then
		mkdir build/bin/debug/include
	fi

	cp -r include/GLSL/ 'build/bin/debug/include/'

	# Run
	headerStart "Run"
	info "./build/bin/debug/Caze-Core"
	./build/bin/debug/Caze-Core
	headerEnd
	
elif [[ $1 == release ]]; then

	mode="RELEASE"

	createandcopy

	# build
	headerStart "Compiling Source Code"
	g++ -c ./build/target/*.cpp ./build/target/*.c -std=c++14 -m64 -O3 -Wall -I include/Caze -I include/vendor
	compiledFiles=(./*.o)
	for files in "${compiledFiles[@]}"
	do
		info "${files}"
	done
	headerEnd

	# move compiled file
	removeandmove

	# # build all the obj file
	headerStart "Building compiled files"
	g++ -g ./build/target/*.o -o build/bin/release/Caze-Core -s -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl
	info "Caze-Core"
	headerEnd

	if [ ! -d "build/bin/release/include" ]; then
		mkdir build/bin/release/include
	fi

	cp -r include/GLSL/ 'build/bin/release/include/'

	# Run
	headerStart "Run"
	info "./build/bin/release/Caze-Core"
	./build/bin/release/Caze-Core
	headerEnd
fi