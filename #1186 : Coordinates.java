//hihocoder-1186
//calc divisor
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class Main {
	static Scanner scanner;
	static boolean debug=false;
	int P,Q;
	List<Integer> pList=new ArrayList<>();
	List<Integer> qList=new ArrayList<>();
	
	void read(){
		P=scanner.nextInt();
		Q=scanner.nextInt();
	}
	void calcDivisor(int x,List<Integer> list){
		int j=0;
		for(int i=1;i<=Math.sqrt(x);i++)
			if(x%i==0){
				list.add(i);
				if(i!=(j=x/i))
					list.add(j);
			}
		Collections.sort(list);
	}
	void calc(){
		calcDivisor(P,pList);
		calcDivisor(Q,qList);
	}
	void output(){
		for(int p: pList)
			for(int q:qList)
				System.out.println(p+" "+q);
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		scanner=new Scanner(System.in);
		if(debug)
			scanner=new Scanner(new File("d:/in.txt"));
		Main obj= new Main();
			obj.read();
			obj.calc();
			obj.output();
	}

}
