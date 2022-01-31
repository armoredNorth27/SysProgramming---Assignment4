Compiling instructions:
    There is nothing fancy when it comes to compiling and running my solution.
    Once you've navigated to the folder that contains the contents of my tar
    file, run the command "make main". This will compile all the necessary files
    along with generating an executable file called "main". So after everything
    is compiled, run the command "./main" and the program should be run. If you
    want to clean all of the object files along with the executable that's created,
    run the command "make clean". This will remove all .o and executable files while
    still leaving everything else.
    
    Note: When compiling all the files, my compiler complained that it couldn't read
    the sort_refugees() function that I made for the bonus marks. I think the reason
    for this is because I didn't include the sort_refugees() function inside of the
    header file. I asked the Professor and she told me that it's better not to change
    the header file so I decided not to touch it. The only thing I changed was 
    increasing the size of the MAX_ID variable to 11 from 10 because she let me know
    that it was originally supposed to be equal to 11. That being said, I only created
    the sort_refugees() function inside of my refugee.c file, but I still call it inside
    main.c. The program runs just fine despite the compiler warnging and it still allows 
    me to use the function so I'm hoping it won't be an issue on your end when you test it.
