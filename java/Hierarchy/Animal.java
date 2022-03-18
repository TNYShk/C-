
public class Animal {

	static String typeOfAminal;
	
	public void makeNoise() {
		System.out.println("this is your Animal captain speaking");
	}
	
}

class Dog extends Animal{
	
	String name;
	protected int age;
	
	public Dog(String name, int age) {
		this.name = name;
		this.age = age;
		System.out.println("weve seem to fly into dog");
		Dog.typeOfAminal= new String("Dog");	
	}
	
	public void getAge() {
		System.out.println("Dog's age is " + age);
	}
	@Override
	public void makeNoise() {
		System.out.println("bark woof!");
	}
}

class Wolf extends Dog{

	public Wolf(String name, int age) {
		super(name, age);
		System.out.println("turbulence, in WOLF constructor");
		Wolf.typeOfAminal = new String("Wolf");
	}
	
	public void getAge() {
		System.out.println("Wolf's age is " + age);
	}
	@Override
	public void makeNoise() {
		System.out.println("Wolf growls");
	}
	
	
	
}

/*
public static void setType(String type) {
	typeOfAminal = type;
	System.out.println("Animal type is:" + typeOfAminal);
}
*/



