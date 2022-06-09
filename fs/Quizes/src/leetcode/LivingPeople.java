package leetcode;

import java.util.*;

//given a list of people with the DoB and DoD, compute the year with the most number of people alive, assuming all born between 1900-2000 included
public class LivingPeople {
    public Person[] population;

    public LivingPeople(){
       this(20);
    }
    public LivingPeople(int many){
        population = new Person[many];
        for(int i = 0; i< population.length;++i){
            int birthday = (int) Math.floor(Math.random() *(2000-1900)+ 1900);
            int deathhday = (int) Math.floor(Math.random() * (2000-birthday+1)+ birthday);
            population[i] = new Person(birthday,deathhday);
        }
    }
    public void printDeaths(){
        for(int i= 0;i<population.length;++i){
            System.out.println("person "+ i+ " died in "+ population[i].getDeathYear());
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

    public int mostPeopleAlive(){
        HashMap<Integer,Integer> years = new HashMap<>(100);
        for(int i =0; i< population.length;++i){

            for(int j = population[i].getBirth();j< population[i].deathYear; ++j ){
                years.merge((2000-j),1,Integer::sum);
            }
        }
        int key = Collections.max(years.values());
        int maxYear = 0;
       /* System.out.println(years.keySet());
        System.out.println(years.values());*/
        for(Map.Entry<Integer,Integer> entry: years.entrySet()){
            if(entry.getValue().equals(key))
                maxYear = entry.getKey();
        }
        return 2000- maxYear;
    }

    public static void main(String[] args){
        LivingPeople test = new LivingPeople(3);

        test.printBirthsDeaths();
        System.out.println(test.mostPeopleAlive());

    }


}
