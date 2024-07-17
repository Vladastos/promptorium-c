#!/bin/sh
PROMPTORIUM_LOG_DIR=/home/vlad/Documents/promptorium-c/shell

generate_ipc_key() {
    #generate a 16 digit random number
    echo $(( $RANDOM ** 4 % 10000000000 ))
}

log(){
    log_level=$1
    message=$2
    timestamp=$(date +"%Y-%m-%d %H:%M:%S")
    echo "[ $timestamp ] [ $log_level ] $message" >> $PROMPTORIUM_LOG_DIR/promptorium.log
}

cleanup(){
    log "INFO" "removing shared memory segment for promptorium configuration $PROMPTORIUM_IPC_KEY"
    # remove shared memory segment
    promptorium cleanup --debug &&
    log "INFO" "shared memory segment removed" ||
    log "ERROR" "failed to remove shared memory segment"
}

main(){
    export PROMPTORIUM_IPC_KEY=$(generate_ipc_key)
    log "INFO" "ipc key generated: $PROMPTORIUM_IPC_KEY "
    # create a shared memory segment key
    log "INFO" "starting promptorium configuration"
    # load promptorium configuration
    promptorium init --debug && 
    log "INFO" "promptorium configuration loaded" ||
    log "ERROR" "promptorium configuration failed"
    # set prompt command
}

#function to be called on exit
trap cleanup EXIT

main