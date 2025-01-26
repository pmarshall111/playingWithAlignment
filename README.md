# Playing with alignment

## Usage

```
peter@chronos:~/Documents/personalProjects/alignment$ make run_speed
./build/speedTest.tsk
Total memory allocated by compiler (mb): 1600
Total memory allocated by me (mb): 900
Write non aligned arr linear access execution time: 4730
Write compiler arr linear access execution time: 4493
Write non aligned arr random access execution time: 6721
Write compiler arr random access execution time: 6798
Write non aligned arr linear access execution time: 4615
Write compiler arr linear access execution time: 4472
Write non aligned arr random access execution time: 6756
Write compiler arr random access execution time: 6845
Write non aligned arr linear access execution time: 4594
Write compiler arr linear access execution time: 4515
Write non aligned arr random access execution time: 7251
Write compiler arr random access execution time: 7163
Write non aligned arr linear access execution time: 4692
Write compiler arr linear access execution time: 4516
Write non aligned arr random access execution time: 6796
Write compiler arr random access execution time: 6917
Write non aligned arr linear access execution time: 4643
Write compiler arr linear access execution time: 4527
Write non aligned arr random access execution time: 6772
Write compiler arr random access execution time: 6852
```

## Results

| Write type | Alignment type | Avg time (ms) |
| --- | --- | --- |
| Linear | Aligned |  4284.6 |
| Linear | NON-Aligned |  4654.8 |
| Random | Aligned |  6915.0 |
| Random | NON-Aligned |  6859.2 |

| Write type | Time diff ms | Time diff perc |
| --- | --- | --- |
| Linear | 370.2 (Aligned faster) | 8% |
| Random | 55.8 (Non aligned faster) | 0.8% |

## Conclusion

- Linear writes were slightly faster for aligned data. It should be noted that the aligned data spanned nearly double of the non-aligned data (1.6GB vs 0.9GB)
- Random writes were effectively the same for aligned and non-aligned data
- This test probably doesn't have a big enough difference to confidently say aligned data is faster than non-aligned data.