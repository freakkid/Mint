import static org.junit.Assert.*;
import imagereader.IImageIO;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.image.*;
import java.awt.*;
import java.io.*;

import javax.imageio.ImageIO;

import org.junit.Test;


public class ImplementImageProcesserTest {
	public ImplementImageIO imageioer = new ImplementImageIO();
	public ImplementImageProcesser processer = new ImplementImageProcesser();
	
	@Test
	public void GrayTest1() throws IOException {
		
		Image test_image = processer.showGray(imageioer.myRead("/home/administrator/Workspace/s/src/goal/1.bmp"));
		
		File sourceImage = new File("/home/administrator/Workspace/s/src/goal/1_gray_goal.bmp");
		Image goal_image = ImageIO.read(sourceImage);

		// compare width and height 
		assertEquals(test_image.getHeight(null), goal_image.getHeight(null));
		assertEquals(test_image.getWidth(null), goal_image.getWidth(null));
		
		BufferedImage test_bimage = new BufferedImage(test_image.getWidth(null), test_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D test_bGr = test_bimage.createGraphics();
    	test_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	test_bGr.dispose();
    	
    	BufferedImage goal_bimage = new BufferedImage(goal_image.getWidth(null), goal_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D goal_bGr = goal_bimage.createGraphics();
    	goal_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	goal_bGr.dispose();
    	
    	// 
		for (int i = 0; i < goal_bimage.getWidth(); i++)
		{
			for (int j = 0; j < goal_bimage.getHeight(); j++)
			{
				assertEquals(goal_bimage.getRGB(i, j), test_bimage.getRGB(i, j));
			}
		}
    	
	}
	
	@Test
	public void GrayTest2() throws IOException {
		
		Image test_image = processer.showGray(imageioer.myRead("/home/administrator/Workspace/s/src/goal/2.bmp"));
		
		File sourceImage = new File("/home/administrator/Workspace/s/src/goal/2_gray_goal.bmp");
		Image goal_image = ImageIO.read(sourceImage);

		// compare width and height 
		assertEquals(test_image.getHeight(null), goal_image.getHeight(null));
		assertEquals(test_image.getWidth(null), goal_image.getWidth(null));
		
		BufferedImage test_bimage = new BufferedImage(test_image.getWidth(null), test_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D test_bGr = test_bimage.createGraphics();
    	test_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	test_bGr.dispose();
    	
    	BufferedImage goal_bimage = new BufferedImage(goal_image.getWidth(null), goal_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D goal_bGr = goal_bimage.createGraphics();
    	goal_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	goal_bGr.dispose();
    	
    	// 
		for (int i = 0; i < goal_bimage.getWidth(); i++)
		{
			for (int j = 0; j < goal_bimage.getHeight(); j++)
			{
				assertEquals(goal_bimage.getRGB(i, j), test_bimage.getRGB(i, j));
			}
		}
    	
	}

	@Test
	public void RedTest1() throws IOException {
		
		Image test_image = processer.showChanelR(imageioer.myRead("/home/administrator/Workspace/s/src/goal/1.bmp"));		
		File sourceImage = new File("/home/administrator/Workspace/s/src/goal/1_red_goal.bmp");
		Image goal_image = ImageIO.read(sourceImage);

		// compare width and height 
		assertEquals(test_image.getHeight(null), goal_image.getHeight(null));
		assertEquals(test_image.getWidth(null), goal_image.getWidth(null));
		
		BufferedImage test_bimage = new BufferedImage(test_image.getWidth(null), test_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D test_bGr = test_bimage.createGraphics();
    	test_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	test_bGr.dispose();
    	
    	BufferedImage goal_bimage = new BufferedImage(goal_image.getWidth(null), goal_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D goal_bGr = goal_bimage.createGraphics();
    	goal_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	goal_bGr.dispose();
    	
		for (int i = 0; i < goal_bimage.getWidth(); i++)
		{
			for (int j = 0; j < goal_bimage.getHeight(); j++)
			{
				assertEquals(goal_bimage.getRGB(i, j), test_bimage.getRGB(i, j));
			}
		}
    	
	}
	
	@Test
	public void RedTest2() throws IOException {
		
		Image test_image = processer.showChanelR(imageioer.myRead("/home/administrator/Workspace/s/src/goal/2.bmp"));
		
		File sourceImage = new File("/home/administrator/Workspace/s/src/goal/2_red_goal.bmp");
		Image goal_image = ImageIO.read(sourceImage);

		// compare width and height 
		assertEquals(test_image.getHeight(null), goal_image.getHeight(null));
		assertEquals(test_image.getWidth(null), goal_image.getWidth(null));
		
		BufferedImage test_bimage = new BufferedImage(test_image.getWidth(null), test_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D test_bGr = test_bimage.createGraphics();
    	test_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	test_bGr.dispose();
    	
    	BufferedImage goal_bimage = new BufferedImage(goal_image.getWidth(null), goal_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D goal_bGr = goal_bimage.createGraphics();
    	goal_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	goal_bGr.dispose();
    	
    	// 
		for (int i = 0; i < goal_bimage.getWidth(); i++)
		{
			for (int j = 0; j < goal_bimage.getHeight(); j++)
			{
				assertEquals(goal_bimage.getRGB(i, j), test_bimage.getRGB(i, j));
			}
		}
    	
	}
	
	
	
	@Test
	public void GreenTest1() throws IOException {
		
		Image test_image = processer.showChanelG(imageioer.myRead("/home/administrator/Workspace/s/src/goal/1.bmp"));		
		File sourceImage = new File("/home/administrator/Workspace/s/src/goal/1_green_goal.bmp");
		Image goal_image = ImageIO.read(sourceImage);

		// compare width and height 
		assertEquals(test_image.getHeight(null), goal_image.getHeight(null));
		assertEquals(test_image.getWidth(null), goal_image.getWidth(null));
		
		BufferedImage test_bimage = new BufferedImage(test_image.getWidth(null), test_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D test_bGr = test_bimage.createGraphics();
    	test_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	test_bGr.dispose();
    	
    	BufferedImage goal_bimage = new BufferedImage(goal_image.getWidth(null), goal_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D goal_bGr = goal_bimage.createGraphics();
    	goal_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	goal_bGr.dispose();
    	
		for (int i = 0; i < goal_bimage.getWidth(); i++)
		{
			for (int j = 0; j < goal_bimage.getHeight(); j++)
			{
				assertEquals(goal_bimage.getRGB(i, j), test_bimage.getRGB(i, j));
			}
		}
    	
	}
	
	@Test
	public void GreenTest2() throws IOException {
		
		Image test_image = processer.showChanelR(imageioer.myRead("/home/administrator/Workspace/s/src/goal/2.bmp"));
		
		File sourceImage = new File("/home/administrator/Workspace/s/src/goal/2_green_goal.bmp");
		Image goal_image = ImageIO.read(sourceImage);

		// compare width and height 
		assertEquals(test_image.getHeight(null), goal_image.getHeight(null));
		assertEquals(test_image.getWidth(null), goal_image.getWidth(null));
		
		BufferedImage test_bimage = new BufferedImage(test_image.getWidth(null), test_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D test_bGr = test_bimage.createGraphics();
    	test_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	test_bGr.dispose();
    	
    	BufferedImage goal_bimage = new BufferedImage(goal_image.getWidth(null), goal_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D goal_bGr = goal_bimage.createGraphics();
    	goal_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	goal_bGr.dispose();
    	
    	// 
		for (int i = 0; i < goal_bimage.getWidth(); i++)
		{
			for (int j = 0; j < goal_bimage.getHeight(); j++)
			{
				assertEquals(goal_bimage.getRGB(i, j), test_bimage.getRGB(i, j));
			}
		}
    	
	}
	
	@Test
	public void BlueTest1() throws IOException {
		
		Image test_image = processer.showChanelR(imageioer.myRead("/home/administrator/Workspace/s/src/goal/1.bmp"));		
		File sourceImage = new File("/home/administrator/Workspace/s/src/goal/1_blue_goal.bmp");
		Image goal_image = ImageIO.read(sourceImage);

		// compare width and height 
		assertEquals(test_image.getHeight(null), goal_image.getHeight(null));
		assertEquals(test_image.getWidth(null), goal_image.getWidth(null));
		
		BufferedImage test_bimage = new BufferedImage(test_image.getWidth(null), test_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D test_bGr = test_bimage.createGraphics();
    	test_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	test_bGr.dispose();
    	
    	BufferedImage goal_bimage = new BufferedImage(goal_image.getWidth(null), goal_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D goal_bGr = goal_bimage.createGraphics();
    	goal_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	goal_bGr.dispose();
    	
		for (int i = 0; i < goal_bimage.getWidth(); i++)
		{
			for (int j = 0; j < goal_bimage.getHeight(); j++)
			{
				assertEquals(goal_bimage.getRGB(i, j), test_bimage.getRGB(i, j));
			}
		}
    	
	}
	
	@Test
	public void BlueTest2() throws IOException {
		
		Image test_image = processer.showChanelR(imageioer.myRead("/home/administrator/Workspace/s/src/goal/2.bmp"));
		
		File sourceImage = new File("/home/administrator/Workspace/s/src/goal/2_blue_goal.bmp");
		Image goal_image = ImageIO.read(sourceImage);

		// compare width and height 
		assertEquals(test_image.getHeight(null), goal_image.getHeight(null));
		assertEquals(test_image.getWidth(null), goal_image.getWidth(null));
		
		BufferedImage test_bimage = new BufferedImage(test_image.getWidth(null), test_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D test_bGr = test_bimage.createGraphics();
    	test_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	test_bGr.dispose();
    	
    	BufferedImage goal_bimage = new BufferedImage(goal_image.getWidth(null), goal_image.getHeight(null), BufferedImage.TYPE_INT_RGB);
    	Graphics2D goal_bGr = goal_bimage.createGraphics();
    	goal_bGr.drawImage(test_bimage, 0, 0, Color.WHITE, null);
    	goal_bGr.dispose();
    	
    	// 
		for (int i = 0; i < goal_bimage.getWidth(); i++)
		{
			for (int j = 0; j < goal_bimage.getHeight(); j++)
			{
				assertEquals(goal_bimage.getRGB(i, j), test_bimage.getRGB(i, j));
			}
		}
    	
	}
	

}
	