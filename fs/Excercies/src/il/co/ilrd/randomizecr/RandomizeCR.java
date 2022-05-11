package il.co.ilrd.randomizecr;

import java.time.LocalDate;
import java.util.*;

public class RandomizeCR {
    List<String> reviewers;
    List<String> reviewees;

    public RandomizeCR(List<String> names) {
        fixPrint(names);
        reviewers = new ArrayList<>(names);
        reviewees = new ArrayList<>(names);
        Collections.shuffle(reviewees);
        improve(reviewees);
    }

    public static void fixPrint(List<String> list) {
        String maxString = Collections.max(list, Comparator.comparingInt(String::length));
        int max = maxString.length();
        for (int j = 0; j < list.size(); ++j) {
            StringBuilder str = new StringBuilder(list.get(j));
            for (int i = 0; i < max - list.get(j).length(); ++i) {
                str = str.append(" ");
            }
            String str2 = new String(str);
            list.set(j, str2);
        }
    }

    public void tanyaCodeReview() {
        boolean flag = false;

        for (int i = 0; i < reviewers.size(); ++i) {
            if (reviewers.get(i).equals(reviewees.get(i))) {
                flag = true;
                break;
            }
        }

        if (flag) {
            improve(reviewees);
        }

        for (int i = 0; i < reviewers.size(); ++i) {
            System.out.println(reviewers.get(i) + " --> " + reviewees.get(i));
        }
    }

    public void improve(List<String> reviewees) {
        LocalDate currentdate = LocalDate.now();
        Collections.rotate(reviewees, currentdate.getDayOfMonth());
    }

    public static void main(String[] args) {
        String[] names = {"Shoshana", "Ori", "Ofer", "Dor", "Tanya", "Nurit", "Shai",
                "Adrian", "Amit", "Daniela", "Ellie", "Shiraz", "Yehuda", "Polina"};

        List<String> nameAsList = Arrays.asList(names);

        RandomizeCR cr = new RandomizeCR(nameAsList);
        System.out.println("Reviewer : Reviewee");
        cr.tanyaCodeReview();
    }

}
