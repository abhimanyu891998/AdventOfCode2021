def part2():
    with open('./input.txt') as f:
        lines = f.read().splitlines()
        count =  0
        for line in lines:
            input, opset = [[set(x) for x in part.split()] for part in line.split('|')]
            nums = {}
            nums[1] = next(x for x in input if len(x)==2)
            input.remove(nums[1])
            nums[4] = next(x for x in input if len(x)==4)
            input.remove(nums[4])
            nums[7] = next(x for x in input if len(x)==3)
            input.remove(nums[7])
            nums[8] = next(x for x in input if len(x)==7)
            input.remove(nums[8])
            nums[9] = next(x for x in input if len(x) == 6 and len(x^(nums[7]|nums[4])) == 1)
            input.remove(nums[9])
            nums[0] = next(x for x in input if len(x) ==6 and nums[1]<x)
            input.remove(nums[0])
            nums[6] = next(x for x in input if len(x) ==6)
            input.remove(nums[6])            
            nums[3] = next(x for x in input if len(x) == 5 and nums[1]<x)
            input.remove(nums[3])
            nums[5] = next(x for x in input if len(nums[9] - x) == 1)
            input.remove(nums[5])
            nums[2] = input.pop()
            
            count += int(''.join(str(next(k for k, v in nums.items() if n == v)) for n in opset))
        return count


def countUnique(input, maininput):
    with open('./input.txt') as f:
        lines = f.read().splitlines()
        count = 0;
        unique = [2,4,3,7]
        for line in lines:
            input = [i for i in (line.split('|')[1]).split(' ')]
            for i in input:
                if (len(i) in unique):
                    count = count + 1;
        print(count)