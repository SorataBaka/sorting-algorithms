all: bin/bucket bin/insert bin/bubble bin/shaker bin/quick
bin/bucket: bucket.c
	gcc bucket.c -o bin/bucket
bin/insert: insert.c
	gcc insert.c -o bin/insert
bin/bubble: bubble.c
	gcc bubble.c -o bin/bubble
bin/shaker: shaker.c
	gcc shaker.c -o bin/shaker
bin/quick: quick.c
	gcc quick.c -o bin/quick