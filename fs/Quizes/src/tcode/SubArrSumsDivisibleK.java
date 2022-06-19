package tcode;

public class SubArrSumsDivisibleK {
    //My solution, exceeds runtime. its O(N*N)- sliding window
    public int subarraysDivByK(int[] nums, int k) {
        int len = nums.length;
        if(len%k ==0)
            return subarrDivByK(nums,k);

        int counter = 0;
        while(len >0){
            int start = 0;
            int localEnd = len;
            while(localEnd<=nums.length){
                if(localSum(nums,start,localEnd) %k== 0){
                    ++counter;
                }
                ++start;
                ++localEnd;
            }
            --len;
        }

        return counter;
    }


    private int localSum(int[]nums, int start, int end){
        int sum = 0;
        for(int i=start; i<end;++i){
            sum +=nums[i];
        }
        return sum;
    }

    public int subarrDivByK(int[] A, int K) {
        //There K mod groups 0...K-1
        //For each prefix sum that does not have a remainder, it needs to be paired with 1 with the same remainder
        //this is so the remainders cancel out.
        int N = A.length;
        int[] modGroups = new int[K];
        int sum = 0;
        for (int i = 0; i < N; i++){
            sum += A[i];
            int group = sum % K;

            if (group < 0) group += K; //Java has negative modulus so correct it
            modGroups[group]++;
        }

        int total = 0;
        for (int x : modGroups){
            if (x > 1) total += (x*(x-1)) / 2;
        }
        //Dont forget all numbers that divide K
        return total + modGroups[0];
    }

    public static void main(String[] args){
        SubArrSumsDivisibleK test = new SubArrSumsDivisibleK();
        int[]nums = {4,5,0,-2,-3,1};
        int[]num1 = {5};
        int[]num3 = {0,-5};
        int[]num4 = {-6,1,-5,10};
        //System.out.println(test.subarraysDivByK(nums,5));
        //System.out.println(test.subarraysDivByK(num1,9));
        // System.out.println(test.subarraysDivByK(num3,10));
        //System.out.println(test.subarraysDivByK(num4,9));

    }
}
