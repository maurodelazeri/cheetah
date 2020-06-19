# cheetah
Zinnion XPUB/XPUB proxy router

![XPUB / XSUB Proxy](xpubxsub.png)

cmake .. -DCMAKE_BUILD_TYPE=Release && make -j4 && mkdir bin && mv cheetah bin && tar -czvf cheetah.tar.gz bin/cheetah && mc cp cheetah.tar.gz minio/app/

cmake .. -DCMAKE_BUILD_TYPE=Release && make -j4 && scp cheetah mauro@64.111.209.150:

