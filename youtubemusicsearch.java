

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.FileReader;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;

public class youtubemusicsearch {

	public void running() throws IOException
	{
		int kk=0;
		String ____filename = "music_2022_05_21";
		BufferedReader reader = new BufferedReader(new FileReader(____filename + ".txt"));

		String str;
        while ((str = reader.readLine()) != null) 
		{
			musictowrite(____filename + "_" +  Integer.toString(kk), search(str));

			kk++;
			if(kk>2) break;
        }
        reader.close();
	}
	public String search(String search) throws IOException {
		
		String apiurl = "https://www.googleapis.com/youtube/v3/search";
		apiurl += "?key=AIzaSyBNUVdZBk1vvsmR9AOSjRQcnpU93K0rnH8";
		apiurl += "&part=snippet&type=video&maxResults=20&videoEmbeddable=true";
		//apiurl += "&part=id&type=video&maxResults=20&videoEmbeddable=true";
		apiurl += "&q="+URLEncoder.encode(search,"UTF-8");

        System.out.println("--------------------------------------------------------");
		System.out.println(apiurl);
		System.out.println("--------------------------------------------------------");
		
		URL url = new URL(apiurl);
		HttpURLConnection con = (HttpURLConnection) url.openConnection();
		con.setRequestMethod("GET");
		
		BufferedReader br = new BufferedReader(new InputStreamReader(con.getInputStream(),"UTF-8"));
		String inputLine;
		StringBuffer response = new StringBuffer();
		while((inputLine = br.readLine()) != null) {
			response.append(inputLine);
		}
		br.close();
		
		return response.toString();
	}
	public void musictowrite(String ____wfilename, String str) throws IOException
	{
		File file = new File("./jsonmusic/" + ____wfilename + ".json");

		try 
		{
			BufferedWriter writer = new BufferedWriter(new FileWriter(file));
			writer.write(str);

			System.out.println("--------------------------------------------------------");
			System.out.println("[FILENAME}:" + "./jsonmusic/" + ____wfilename + ".json");
			System.out.println(str);
			System.out.println("--------------------------------------------------------");

			writer.close();
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	}
}