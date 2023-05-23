touch kourosh.txt
touch yours.txt
echo "" > kourosh.txt
echo "" > yours.txt
g++ -std=c++17 -o gen gen.cpp 2> /dev/null
((i = 1)) 2> /dev/null
while diff kourosh.txt yours.txt > /dev/null
do
  echo $i
  ((i++)) 2> /dev/null
  ./gen
  ./kourosh < input.txt > kourosh.txt
  ./yours < input.txt > yours.txt
done
code --diff kourosh.txt yours.txt
