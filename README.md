# Gossip

```bash
make protoc
make client

#在不同的终端上
./client c0 0.0.0.0:50051 localhost:50052 localhost:50053
./client c1 0.0.0.0:50052 localhost:50051 localhost:50053
./client c2 0.0.0.0:50053 localhost:50051 localhost:50052

#在命令行任意输入，进行当前client时间戳更新
```

