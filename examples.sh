for cpp in $(find ./examples -name "*.cpp")
do

  name=$(echo $basename $cpp | sed 's/\.[^.]*$//')
  
  echo $name

  g++ ${name}.cpp -lfdc -o ${name}.run && ${name}.run > ${name}.txt

  rm ${name}.run

done
