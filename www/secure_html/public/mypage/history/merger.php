<?php
//Import file
require_once ('PDFMerger.php');
use PDFMerger\PDFMerger;
$pdf = new PDFMerger;

if( $_SERVER['REQUEST_METHOD']=='GET') {
	// getting file from server
	

	// Connecting to FTP
	$host = "kh01.kyoto-happy.co.jp";
	$user = 'kh00012g';
	$password = 'H%6LpaY8eeBc$M';

	// Connect to host
	$conn = ftp_connect($host);
	if(!$conn) {
		echo 'Error: could not connect to ftp server</br>';
		exit;
	}
	// login in ftp
	$result = ftp_login($conn, $user, $password);
	if(!$result){
		echo "Error: could not log on as ".$user."</br>"; 
		ftp_quit($conn);
		exit;
	}

	// try to change the directory to PDF directory
	if (ftp_chdir($conn, "/secure_html/PDF_Document/")) {
		// echo "Current directory is now: " . ftp_pwd($conn) . "<br>";
	} else { 
		echo "Couldn't change directory<br>";
	}
	// set passive on
	ftp_pasv($conn, true);

	for($i=1; $i<= 2; $i++) {
		// Connecting to FTP
	$host = "kh01.kyoto-happy.co.jp";
	$user = 'kh00012g';
	$password = 'H%6LpaY8eeBc$M';

	// Connect to host
	$conn = ftp_connect($host);
	if(!$conn) {
		echo 'Error: could not connect to ftp server</br>';
		exit;
	}
	// login in ftp
	$result = ftp_login($conn, $user, $password);
	if(!$result){
		echo "Error: could not log on as ".$user."</br>"; 
		ftp_quit($conn);
		exit;
	}

	// try to change the directory to PDF directory
	if (ftp_chdir($conn, "/secure_html/PDF_Document/")) {
		// echo "Current directory is now: " . ftp_pwd($conn) . "<br>";
	} else { 
		echo "Couldn't change directory<br>";
	}
	// set passive on
	ftp_pasv($conn, true);

		$remotefile_cov = 'remotefile'.$i;
		$remotefile_1 = $_GET[$remotefile_cov];
		// echo $remotefile_1."<br>";;
		$remotefile = iconv("UTF-8", "SJIS", $remotefile_1);
		$localfile = 'mergefilename'.$i.'.pdf';
		// echo $localfile."<br>";
		// open local file for writing
		$fp = fopen($localfile, 'w');
		// write remote file into localfile
		if(!$success = ftp_fget($conn, $fp, $remotefile, FTP_BINARY)){
			session_start();
			// $_SESSION['error_download'] = "Starting page, is greater than ending page";
			echo "ファイルが見つかりませんでした。";
			// echo "<script>window.close();</script>";
			// echo "<script>window.close();</script>";
			// return $res;
			exit;
		}
	}
}
//Create object of PDFMerger to mearge pdf files.

$pdf->addPDF('mergefilename1.pdf');          //Pass file name with location
$pdf->addPDF('mergefilename2.pdf');      //Pass specific page number
// $pdf->addPDF('12.pdf','1-2');    //Include specific page


$pdf->merge('browser');         //To open with browser

// $pdf->merge('download','new.pdf');    To Download file with name 
// $pdf->merge('file','/aa.pdf');         //To open with browser
// $pdf->merge('browser');         //To open with browser
	
	//REPLACE 'file' WITH 'browser', 'download', 'string', or 'file' for output options
	//You do not need to give a file path for browser, string, or download - just the name.
