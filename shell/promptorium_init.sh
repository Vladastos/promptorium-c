#!usr/bin/sh

generate_ipc_key() {
    #generate a 16 digit random number
    echo $(( $RANDOM ** 4 % 1000000000000000 ))
}

export PROMPTORIUM_IPC_KEY=$(generate_ipc_key)

main() {
    # create a shared memory segment key

    # load promptorium configuration


}

#function to be called on exit
cleanup(){
    # unload promptorium configuration

    # remove shared memory segment
}

trap cleanup EXIT

main