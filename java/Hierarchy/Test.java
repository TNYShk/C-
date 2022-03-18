
public class Test {

	public static void main(String[] args) {
		
		
		Animal myAnimal = new Dog("Twinky",11);
			System.out.println(myAnimal.typeOfAminal);
		
			Animal horse = new Animal();
		Animal.typeOfAminal = "Horse";
		System.out.println(Animal.typeOfAminal);
		
		doAnimalStuff(myAnimal);
		((Dog)myAnimal).getAge();
		
		
		doAnimalStuff(horse);
		Wolf aWolf = new Wolf("wolfy", 5);
		System.out.println(Wolf.typeOfAminal);
		doAnimalStuff(aWolf);
		aWolf.getAge();
		
	}
public static void doAnimalStuff(Animal animal) {
	animal.makeNoise();
}
}

