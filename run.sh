# runs the program with one command
#g++ -o sphereGL app.cpp app.h main.cpp sphereJK_OO_basic.cpp -lGL -lGLU -lglut && ./sphereGL

echo "#############################################"
echo "#                                           #"
echo "#          Arch Linux & OpenGL              #"
echo "#                                           #"
echo "#############################################"

echo -e "\nChoose Mode:"
echo "1. Assisted"
echo "2. Advanced"
read mode

if [ $mode == 2 ]; then
    echo -n "Enter output file name (default: output): "
    read output
    output=${output:-output}

    echo -n "Enter main entry point (default: main.cpp): "
    read main_file
    main_file=${main_file:-main.cpp}

    echo -n "Enter other dependencies (default: app.cpp app.h sphereJK_OO_basic.cpp): "
    read dependencies
    dependencies=${dependencies:-"app.cpp app.h sphereJK_OO_basic.cpp"}

    echo -n "Enter additional CLI arguments (default: -lGL -lGLU -lglut): "
    read cli_args
    cli_args=${cli_args:-"-lGL -lGLU -lglut"}

else
    output="output"
    main_file="main.cpp"
    dependencies="app.cpp app.h coreMath.h particle.h particle.cpp sphereJK_OO_basic.cpp"
    cli_args="-lGL -lGLU -lglut -lm"
fi

command="g++ -o $output $main_file $dependencies $cli_args && ./$output -std=c++17"

echo "Running command: $command"
eval $command
