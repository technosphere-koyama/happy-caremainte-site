<?php //Import file
require_once ('PDFMerger.php');
use PDFMerger\PDFMerger;
$pdf = new PDFMerger;

    if( $_SERVER['REQUEST_METHOD']=='GET') {
        // getting file from server
        $remotefile = $_GET['chart_id'];

        // Connecting to FTP
        $host = "kh01.kyoto-happy.co.jp";
        $user = 'kh00012g';
        $password = 'H%6LpaY8eeBc$M';
        
        //$remotefile = iconv("UTF-8", "SJIS", $remotefile_1);
        $localfile = 'filename.pdf';

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
        // open local file for writing
        $fp = fopen($localfile, 'w');
        // write remote file into localfile
        if(!$success = ftp_fget($conn, $fp, $remotefile, FTP_BINARY)){
            // echo 'Could not download file</br>';
            echo "ファイルが見つかりませんでした。";
            ftp_quit($conn);
            exit;
        } else {
            // prepare for download
            // fclose($fp);
            // $fsize = filesize($localfile);
            // header("Content-type: application/pdf"); // add here more headers for diff.     extensions
            // header("Content-Disposition: attachment; filename=\"".$remotefile_1."\""); 
            // header("Content-length: $fsize");
            echo "Success";
            // @readfile($localfile);
            $pdf->addPDF($localfile);          //Pass file name with location
            // $pdf->addPDF('mergefilename2.pdf');      //Pass specific page number
            // $pdf->addPDF('12.pdf','1-2');    //Include specific page


            $pdf->merge('browser'); 
        }	
        //close connection
        ftp_quit($conn);
    }
//  ?>