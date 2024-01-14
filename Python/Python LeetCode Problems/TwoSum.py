class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        # This problem is asking us two values in a list that add up to a target ie (val1 + val2) == target. The way we can approach this is do a for loop that iterates through the entire list. At each iteration, we check if the current value is one of the values we need by subtracting it from the target and seeing if the difference is in the list ie (target - val1) == val2, Note that val1 is the value we are currently at. If the val2 is in fact in the list, then we have found our pair of values that add up to target and can return the index of those two values. The most effective way to check if val2 is in the list and return its index is by using a hashmap. As we iterate through the list, we would add each value we are at to the hashmap and its index value. Later on, one of those values we add to the hashmap will act as "val2" and the if statement will meet the conditions required to return the pair of values. Below is the implementation of this function.
        hashmap = {}
        val2 = 0
        for index in range(len(nums)):
            val2 = target - nums[index]
            if val2 in hashmap:
                return [hashmap[val2], index]
            else:
                hashmap[nums[index]] = index
        return None

        #The time complexity is O(n) since we iterate through the list only one time. The space complexity is O(n) since the size of the hashmap is proportional to the size of the list. By that, I mean the hashmap is added to during each iteration and the number of iterations is based ont he size of the list. In worse case scenario, we have to iterate through the entire list due to val1 we need being the last value in the list. 