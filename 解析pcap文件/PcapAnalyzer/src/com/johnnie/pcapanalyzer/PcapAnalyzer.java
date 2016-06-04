package com.johnnie.pcapanalyzer;

import java.awt.EventQueue;
import java.io.File;
import javax.swing.JFrame;

import com.johnnie.pcapanalyzer.ui.MainFrame;
import com.johnnie.pcapanalyzer.utils.Constant;
import com.johnnie.pcapanalyzer.utils.FileUtils;

/**
 * @author CMM
 */
public class PcapAnalyzer {
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					FileUtils.createDir(Constant.LOG_DIR);
					File recent_log = new File(Constant.LOG_RECENT_FILE);
					if (!recent_log.exists()) {
						FileUtils.createEmpFile(Constant.LOG_RECENT_FILE);
					}
					new MainFrame().setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
}
