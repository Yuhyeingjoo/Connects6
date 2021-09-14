import java.io.*;
import java.net.*;
import java.io.BufferedReader;
import java.util.Date;
import java.util.*;
import java.nio.ByteBuffer;

class Board{
	private int[][] board = new int[20][20];
	private String redStones ; 
	public String getRedstones(){
		return redStones;
	}
	private boolean storeBoard(int a, int b){
		if(this.board[20-b][a]!=-1){
			board[20-b][a] = -1;
			return true;
		}
		else{
			return false;
		}
	}
	private void randTest(char c, int b){
		
		if(c=='I' || c<65 || c>84 || b<1 ||b>19){
			System.out.println("err: "+ c+" "+b);
			System.exit(1);
		}
	}
	public String redStoneGenerater(){
		int a  , b, numberOfRedstones;
		numberOfRedstones = 4;
		String newRedstones ="";
		
		for(int i=0; i<numberOfRedstones; i++){
			while(true){
				a = (int)((Math.random()* 10000)%19);
				if(a!=8) break;
			}
			
			b = (int)((Math.random()*10000)%19)+1;
			char c = (char)(65+a);
			if(storeBoard(a, b)){
				newRedstones = newRedstones+String.valueOf(c);
				if(b<10){
					newRedstones = newRedstones+ Integer.toString(0);
				}
				newRedstones = newRedstones+ Integer.toString(b);
			}
		}
		
		return newRedstones;
	}	
	Board(){
		for(int i = 0; i<20; i++){
			for(int j = 0; j<20; j++){
				this.board[i][j] =0;
			}
		
		}
		this.redStoneGenerater();
	}
	
}

class Server {
	private String color_str, port_str, given_stones;
	private Scanner sc;
	private int port, color;
	private Socket socket;
	private InputStream input;
	private OutputStream out;
	
	
		
	public void init(){
		sc = new Scanner(System.in);
		System.out.println("Input color of stone; 0: black  1: white");
		color_str = sc.nextLine();
		color = Integer.parseInt(color_str);
		System.out.println("Input port num");
		port_str = sc.nextLine();
		port = Integer.parseInt(port_str);
		System.out.println(port+ " "+color);
		try(ServerSocket serverSocket = new ServerSocket(port)){
			socket = serverSocket.accept();
			input  = socket.getInputStream();
			out = socket.getOutputStream();
		}
		catch(IOException e){
			System.out.println("catch");
		}
	}
		
	public byte[] int_to_byte_array(int value){
		 return new byte[] {(byte)(value >>> 24), (byte)(value >>> 16), (byte)(value >>> 8), (byte)value};
	}
	public int recvAll(byte[] buf, int size) {
		int off= 0;;
		try{

			for(off = 0; off == size; ){
				off = input.read(buf,off,size-off);
			}
		}catch (IOException e){
		}
		return off;
	}
	
	public int convertByteArrayToInt(byte[] bytes) {
        	return ByteBuffer.wrap(bytes).getInt();
    	}

	public static void main(String[] args){
		byte [] red_stone, red_size;
		byte[] givenSize = {00}  ;
		int givenIntSize ;
//		Server m = new Server();		
		Board b = new Board();
/*		m.init();			
		
		String given_stone;
			
		red_size = m.int_to_byte_array(5);
		red_stone = "E3G12".getBytes();
			
		System.out.println("size : " + red_size.length+ "data len: "+red_stone.length);
		
		try{	
			m.out.write(red_size,0,4);
			m.out.write(red_stone,0, red_stone.length);
			byte[] givenStone = new byte[3]; 
			m.input.read(givenStone, 0,3);	
			m.given_stones = new String(givenStone);
			System.out.println(m.given_stones);
		}
		catch(IOException e){}
			

*/			
		
	}
}
