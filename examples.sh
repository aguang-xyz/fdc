for cpp in $(find ./examples -name "*.cpp")
do

  name=$(echo $basename $cpp | sed 's/\.[^.]*$//')

  g++ ${name}.cpp -lfdc -o ${name}.out && ${name}.out > ${name}.txt

  echo $name
done
