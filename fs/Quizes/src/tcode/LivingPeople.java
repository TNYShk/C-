package tcode;

import java.util.*;

//given a list of people with the DoB and DoD, compute the year with the most number of people alive, assuming all born between 1900-1999 included
public class LivingPeople {
    public Person[] population;

    public LivingPeople(){
       this(20);
    }
    public LivingPeople(int many){
        population = new Person[many];
        for(int i = 0; i< population.length;++i){
            int birthday = (int) Math.floor(Math.random() *(1999-1900)+ 1900);
            int deathhday = (int) Math.floor(Math.random() * (1999-birthday+1)+ birthday);
            population[i] = new Person(birthday,deathhday);
        }
    }

    public void printBirthsDeaths(){
        for(int i= 0;i<population.length;++i){
            System.out.println("person "+ i+ " born in "+ population[i].getBirth());
            System.out.println("person "+ i+ " died in "+ population[i].getDeathYear());
            System.out.println();
        }
    }

    class Person{
        private int birthYear;
        private int deathYear;

        public Person(int birthYear, int deathYear){
            this.birthYear = birthYear;
            this.deathYear = deathYear;
        }
        public int getBirth(){
            return birthYear;
        }

        public int getDeathYear(){
            return deathYear;
        }

    }
    private int[] getLiving(Person[]people){
        int[]year = new int[people.length];
        for(int i=0; i< population.length;++i){
            year[i] = population[i].getBirth();
        }
        Arrays.sort(year);
        return year;
    }
    private int[] getLDeath(Person[]people){
        int[]year = new int[people.length];
        for(int i=0; i< population.length;++i){
            year[i] = population[i].getDeathYear();
        }
        Arrays.sort(year);
        return year;
    }


    public int getLivingYear(Person[] people) {
        int[] live = getLiving(people);
        int[] death = getLDeath(people);

        LinkedHashMap<Integer, Integer> bestMap = new LinkedHashMap<>();
        bestMap.put(live[0],1);
        for (int i = 1; i < people.length; ++i) {
            Integer current = bestMap.get(live[i-1]);
            bestMap.merge(live[i],current+1,Integer::sum);

        }
        //bestMap.merge(death[0],-1,Integer::sum);
        for(int i = 1; i<people.length;++i){
            Integer current = bestMap.get(live[i-1]);
            //bestMap.put(bestMap.get(i),current-1);
            bestMap.merge(death[i], current-1, Integer::sum);
        }

       return (getBestfromHash(bestMap));
    }
    private int getBestfromHash(Map<Integer,Integer>map) {
        int max = Collections.max(map.values());

        int bestYear = 0;
        for (Map.Entry<Integer, Integer> entry : map.entrySet()) {
            if (entry.getValue().equals(max)) {
                bestYear = entry.getKey();
                break;
            }
        }
        return bestYear;
    }


    public int mostPeopleAlive(){
        HashMap<Integer,Integer> years = new HashMap<>(100);
        for(int i =0; i< population.length;++i){

            for(int j = population[i].getBirth();j< population[i].deathYear; ++j ){
                years.merge((2000-j),1,Integer::sum);
            }
        }
       return 2000- getBestfromHash(years);
    }

    public static void main(String[] args){
        LivingPeople test = new LivingPeople(5);

        test.printBirthsDeaths();
        System.out.println("intuitive solution: "+test.mostPeopleAlive());
        System.out.println("improved: "+test.getLivingYear(test.population));

       System.out.println( test.getUniqueChar("boyswillbeboys"));
    }

    public char getUniqueChar(String str){
        LinkedHashMap<Character,Integer>word = new LinkedHashMap<>(str.length());
        for(int i=0; i<str.length();++i){
            word.merge(str.charAt(i),1,Integer::sum);
        }
        for(Map.Entry<Character,Integer>entry: word.entrySet()){
            if(entry.getValue()==1) {
                Character cc = (entry.getKey());
                return cc;
            }
        }

    return ' ';
    }
}
