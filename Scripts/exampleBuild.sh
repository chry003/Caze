if [ ! -d "./Examples" ]; then
	mkdir Examples
fi

echo "Name of the example:"
read name

mkdir Examples/$name

cp ./bin/debug/main "./Examples/$name/"
cp ./src/main.cpp "./Examples/$name/"