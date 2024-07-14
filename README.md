# promptorium-c

## Introduction

This is an implementation of a terminal prompt builder in C.

## Description

The application is meant to be run at the start of your terminal session with the following command:`promptorium --init`
The application will then create a shared memory segment and save the key to the segment in an environment variable called PROMPTORIUM_IPC_KEY.
This segment will be used by the application to store configuration data which will be accessed when `promptorium --get-prompt` is called.