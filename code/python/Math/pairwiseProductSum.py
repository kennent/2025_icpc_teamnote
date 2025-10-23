# 모든 i<j에 대해 arr[i]*arr[j]의 합
# 1*2 + 1*3 + 1*4 + 2*3 + 2*4 + 3*4
arr = [1,2,3,4]

S = sum(arr)
sum_sq = sum(x*x for x in arr)

result = (S*S - sum_sq) // 2
print(result)  # 35