# liteShell

It is a linux shell with basic features. It supports most funcitonalities including multiple commands execution and running background and foreground processes.

## Running

Run the following commands on your terminal

```bash
git clone https://github.com/shu7bh/liteShell.git
cd liteShell
make
./liteShell
```

## Features

- It is a shell, which has basic features. Multiple commands can be given at the same time separated by `;`
- It accounts for tabs and spaces.
- Accessing history through up and down arrow key
- Different colours for file and directories

## Commands

- cd: Change directory Multiple flags are handled

```bash
  cd
  cd .
  cd ..
  cd ~
  cd dir
```

- echo: prints a message onto the screen

```bash
echo message
```

- ls: Lists directory and flies (flags which can be used are -a and -l)

```bash
ls <dir>
ls -a <dir>
ls -l <dir>
ls -la <dir>
ls -al <dir>
```

- pinfo: Prins the details of a particular process. If no argument is given, it prints details of the foreground process

```sh
pinfo
pinfo <pid>
```

- Foreground process: These are the processes that work in the foreground and execute. We cannot run any other command during this.

```bash
vim
nvim
top
```

To run any process in foreground, type the name of the command the arguments required by it

```bash
command args
```

- Background process: These are the ones that run in the background. Another instance is open in some cases.

```bash
gedit &
emacs &
sleep 5 &
```

To run any process, run & at the end to make it work in the background. Not all processes can be run in the background though

```bash
command args &
```

- repeat: You can use this to repeat the same command multiple times. It takes one argument, i.e. the time in seconds.

```bash
repeat 5 cd ..
```

The above command goes to the 5th parent directory, if it exists. In general, for any command, it has to be executed like this

```bash
repeat n command args
```

- history: Shows the history of the commands input by us. Default is to print the last 10 commands. Can print a max of 20 previous commands.

```bash
history
history 15
```

## Exit

If you want to exit the shell, type exit

## Screenshots

![ss](Pics/ss.png)
