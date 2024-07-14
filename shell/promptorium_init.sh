#!usr/bin/sh

generate_ipc_key() {
    #generate a 16 digit random number
    echo $(( $RANDOM ** 4 % 1000000000000000 ))
}

log(){
    log_level=$1
    message=$2
    timestamp=$(date +"%Y-%m-%d %H:%M:%S")
    echo "[$timestamp] [$log_level] $message" >> /home/vlad/Documents/promptorium-c/shell/promptorium_init.log
}

cleanup(){
    log "INFO" "removing shared memory segment for promptorium configuration $PROMPTORIUM_IPC_KEY"
    # remove shared memory segment
}

main() {
    export PROMPTORIUM_IPC_KEY=$(generate_ipc_key)
    log "INFO" "ipc key generated: $PROMPTORIUM_IPC_KEY "
    # create a shared memory segment key
    log "INFO" "starting promptorium configuration"
    # load promptorium configuration
}

#function to be called on exit
trap cleanup EXIT

main