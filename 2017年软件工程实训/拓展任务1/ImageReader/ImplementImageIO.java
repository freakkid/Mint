import imagereader.IImageIO;
import java.awt.Image;
import java.awt.image.*;
import java.awt.*;
import java.io.*;
import javax.imageio.ImageIO;


public class ImplementImageIO implements IImageIO
{
    public Image myRead(String filepath) throws IOException
    {
    	FileInputStream fileInputStream = new FileInputStream(filepath);
		BufferedInputStream bis = new BufferedInputStream(fileInputStream);
		bis.skip(18);

		byte[] b1 = new byte[4];
		bis.read(b1);
		byte[] b2 = new byte[4];
		bis.read(b2);
		
		int width = byte2Int(b1);
		int height = byte2Int(b2);
		
		
		int skip_num = 0;
		if (width * 3 % 4 != 0)
		{
			skip_num = 4 - width * 3 % 4;
		}
		
		bis.skip(28);

		int[] data = new int[height*width];
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int red = bis.read();
				int green = bis.read();
				int blue = bis.read();
				data[width * (height - i - 1) + j] = 0xff << 24 | (blue & 0xff) << 16 | (green & 0xff) << 8 | (red & 0xff);
				
			}
			if (skip_num != 0)
			{
				bis.skip(skip_num);
			}
		}
		
		bis.close();
		
		return Toolkit.getDefaultToolkit().createImage(new MemoryImageSource(width, height, data, 0, width));
    }

    public Image myWrite(Image image, String filepath) throws IOException
    {
    	BufferedImage bimage = null;
    	if (image instanceof BufferedImage)
    	{
    		bimage = (BufferedImage)image;
    	}
    	else
    	{
    		bimage = new BufferedImage(image.getWidth(null), image.getHeight(null), BufferedImage.TYPE_INT_RGB);
        	Graphics2D bGr = bimage.createGraphics();
        	bGr.drawImage(image, 0, 0, Color.WHITE, null);
        	bGr.dispose();
    	}
    	
    	ImageIO.write(bimage, "bmp", new File(filepath));
    	
    	return bimage;
    }

    static int byte2Int(byte[] b)
    {
    	return (b[3] & 0xff << 24) | (b[2] & 0xff) << 16 | (b[1] & 0xff) << 8 | (b[0] & 0xff);
    }
    
}
	