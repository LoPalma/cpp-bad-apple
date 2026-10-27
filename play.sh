for i in {0..6750}; do
  printf "\033[H"
  cpp -P main.c -DFRAME_NUM=$i
  # usleep 33333
done
