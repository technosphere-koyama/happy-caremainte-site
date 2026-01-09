<?php 
    if( $_SERVER['REQUEST_METHOD']=='POST') {
        print_r($_POST); exit;
        $host = "kh01.kyoto-happy.co.jp";
        $user = 'kh00012g';
        $password = 'H6LpaY8eeBcM';
        $remotefile_1 = "00224527_納品書.pdf";
        $remotefile = mb_convert_encoding($remotefile_1, "SJIS");
        $localfile = 'filename.pdf';

        // Connect to host
        $conn = ftp_connect($host);
        if(!$conn) {
            echo 'Error: could not connect to ftp server</br>';
            exit;
        }

        $result = ftp_login($conn, $user, $password);
        if(!$result){
            echo "Error: could not log on as ".$user."</br>"; 
            ftp_quit($conn);
            exit;
        }

        // try to change the directory to somedir
        if (ftp_chdir($conn, "/secure_html/PDF_Document/")) {

        } else { 
            echo "Couldn't change directory<br>";
        }
        $fp = fopen($localfile, 'w');

        if(!$success = ftp_fget($conn, $fp, $remotefile, FTP_BINARY)){
            echo 'Could not download file</br>';
            ftp_quit($conn);
            exit;
        } else {
            fclose($fp);
            $fsize = filesize($localfile);
            header("Content-type: application/pdf"); // add here more headers for diff.     extensions
            header("Content-Disposition: attachment; filename=\"".$remotefile_1."\""); 
            header("Content-length: $fsize");
            readfile($localfile);
        }	
        //close connection
        ftp_quit($conn);
    }
//  ?>