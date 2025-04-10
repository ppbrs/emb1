
# emb1 

* `3party`
* `app` - root directories of applications.
	* `<application-name-1>`
	* `<application-name-2>`
* `arch` - CPU-architecture-dependent sources.
* `bin`
* `boards`
* `common`
* `docs`
	* `app`
		* `<application-name-1>`
		* `<application-name-2>`
* `host-tests`
* `if`
* `integration-tests`
* `libc`
* `obj`
* `scripts`
* `tools`

***
# app

* The name of the application uses dashes, not underscores.
* `<application-name>.mk` is the application-specific part of the `Makefile`.
* `<application-name>.ld` is the application's linker file.
* Building the application:
	* $ `make <application-name> EMB1_TOOLCHAIN=gnu`
	* $ `make <application-name> EMB1_TOOLCHAIN=llvm`

***



