import imagereader.IImageProcessor;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.image.*;
import java.awt.*;
import java.io.*;

public class ImplementImageProcesser implements IImageProcessor
{
	public Image showChanelR(Image sourceImage)
	{
		BufferedImage bimage = null;
    	if (sourceImage instanceof BufferedImage)
    	{
    		bimage = (BufferedImage)sourceImage;
    	}
    	else
    	{
    		bimage = new BufferedImage(sourceImage.getWidth(null), sourceImage.getHeight(null), BufferedImage.TYPE_INT_RGB);
        	Graphics2D bGr = bimage.createGraphics();
        	bGr.drawImage(sourceImage, 0, 0, Color.WHITE, null);
        	bGr.dispose();
    	}
    	
    	int width = bimage.getWidth();
		int height = bimage.getHeight();
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				int pixel = bimage.getRGB(i, j);
				int red = (pixel & 0xff0000) >> 16;
				int green = (pixel & 0xff00) >> 8;
				int blue = (pixel & 0xff);
				int new_pixel = red << 16;
				bimage.setRGB(i, j, new_pixel);
			}
		}
		return (Image)bimage;
	}
	
	public Image showChanelG(Image sourceImage)
	{
		BufferedImage bimage = null;
    	if (sourceImage instanceof BufferedImage)
    	{
    		bimage = (BufferedImage)sourceImage;
    	}
    	else
    	{
    		bimage = new BufferedImage(sourceImage.getWidth(null), sourceImage.getHeight(null), BufferedImage.TYPE_INT_RGB);
        	Graphics2D bGr = bimage.createGraphics();
        	bGr.drawImage(sourceImage, 0, 0, Color.WHITE, null);
        	bGr.dispose();
    	}
    	
    	int width = bimage.getWidth();
		int height = bimage.getHeight();
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				int pixel = bimage.getRGB(i, j);
				int green = (pixel & 0xff00) >> 8;
				int new_pixel = green << 8;
				bimage.setRGB(i, j, new_pixel);
			}
		}
		return (Image)bimage;
	}
	
	public Image showChanelB(Image sourceImage)
	{
		BufferedImage bimage = null;
    	if (sourceImage instanceof BufferedImage)
    	{
    		bimage = (BufferedImage)sourceImage;
    	}
    	else
    	{
    		bimage = new BufferedImage(sourceImage.getWidth(null), sourceImage.getHeight(null), BufferedImage.TYPE_INT_RGB);
        	Graphics2D bGr = bimage.createGraphics();
        	bGr.drawImage(sourceImage, 0, 0, Color.WHITE, null);
        	bGr.dispose();
    	}
    	
    	int width = bimage.getWidth();
		int height = bimage.getHeight();
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				int pixel = bimage.getRGB(i, j);
				int blue = (pixel & 0xff);
				int new_pixel = blue;
				bimage.setRGB(i, j, new_pixel);
			}
		}
		return (Image)bimage;
	}
	
	public Image showGray(Image sourceImage)
	{
		BufferedImage bimage = null;
    	if (sourceImage instanceof BufferedImage)
    	{
    		bimage = (BufferedImage)sourceImage;
    	}
    	else
    	{
    		bimage = new BufferedImage(sourceImage.getWidth(null), sourceImage.getHeight(null), BufferedImage.TYPE_INT_RGB);
        	Graphics2D bGr = bimage.createGraphics();
        	bGr.drawImage(sourceImage, 0, 0, Color.WHITE, null);
        	bGr.dispose();
    	}
    	
    	int width = bimage.getWidth();
		int height = bimage.getHeight();
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				int pixel = bimage.getRGB(i, j);
				int red = (pixel & 0xff0000) >> 16;
				int green = (pixel & 0xff00) >> 8;
				int blue = (pixel & 0xff);
				int gray = (int)(0.299 * red + 0.587 * green + 0.114 * blue);
				int new_pixel = gray << 16 | gray << 8 | gray;
				bimage.setRGB(i, j, new_pixel);
			}
		}
		return (Image)bimage;
	}
}
