import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandParser {

	public Command fetchCommand() {
		
		try {
			String s = reader.readLine();
			if (s == null) {
				return null;
			}

			// \s+ = 1 or more of a whitespace char
			String[] pieces = s.split("\\s+", 6 /* max command len + 1 */);
			String[] params = new String[pieces.length - 1];
			System.arraycopy(pieces, 1, params, 0, pieces.length - 1);
			
			return new Command(pieces[0], params);
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}

	public Command commandFromRawText(String rawText) {
		String[] pieces = rawText.split("\\s+", 6 /* max command len + 1 */);
		String[] params = new String[pieces.length - 1];
		System.arraycopy(pieces, 1, params, 0, pieces.length - 1);
			
		return new Command(pieces[0], params);
	}
	
	private BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
}
