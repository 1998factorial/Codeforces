def solve(a , b , i , j , n , m):
    if i == n and j == m:
        return [""]
    if i == n and j < m:
        ret = solve(a , b , i , j + 1 , n , m)
        ret2 = []
        for s in ret:
            ret2.append(b[j] + s)
        return ret2
    if i < n and j == m:
        ret = solve(a , b , i + 1 , j , n , m)
        ret2 = []
        for s in ret:
            ret2.append(a[i] + s)
        return ret2
    reta = solve(a , b , i + 1 , j , n , m)
    retb = solve(a , b , i , j + 1 , n , m)
    ret = []
    for s in reta:
        ret.append(a[i] + s)
    for s in retb:
        ret.append(b[j] + s)
    return ret

def interleavings(a, b):
    n = len(a)
    m = len(b)
    ret = solve(a , b , 0 , 0 , n , m)
    ret_set = set(ret)
    ans = []
    for s in ret_set:
        ans.append(s)
    ans.sort()
    return ans

if __name__ == '__main__':
    ret = interleavings('a', 'cd')
    for s in ret:
        print(s)

"""
definition:
solve(a , b , i , j) = list of interleaving strings made from
a[i ... n - 1] and b[j ... m - 1]

for i <= n - 1 and j <= m - 1
solve(a , b , i , j) = 
    each string in solve(a , b , i + 1 , j) , prepend by a[i]
    union
    each string in solve(a , b , i , j + 1) , prepend by b[j]

eg.
a = "ab" , b = "cd"
solve(a , b , 2 , 2) = [""]
solve(a , b , 1 , 1) = ["bd" , "db"]

"""
