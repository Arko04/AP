g++ ExitTest.cpp && ./a.out
if [ $? -eq 0 ];
then
    echo ".sh output: That was a good person!"
else
    echo ".sh output: Toby is the worst!"
fi

