<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
	<meta http-equiv="content-type" content="text/html; charset=utf-8" />
	<title>XSFoundation - API Reference</title>
	<meta name="generator" content="BBEdit 10.5" />
	<link href="../CSS/XSDoc.css" type="text/css" rel="stylesheet" media="all" charset="utf-8" />
</head>
<body>
<?php

require_once dirname( __FILE__ ) . DIRECTORY_SEPARATOR . 'Classes' . DIRECTORY_SEPARATOR . 'XS' . DIRECTORY_SEPARATOR . 'Docset.class.php';

$DOC = new XS_Docset( dirname( __FILE__ ) . DIRECTORY_SEPARATOR . '..' . DIRECTORY_SEPARATOR . 'XML' );

$DOC->setProjectName( 'XSFoundation' );
$DOC->setProjectVersion( '2.0.0-0' );
$DOC->setCopyright( 'XS-Labs &copy; %Y - All Rights Reserved' );
$DOC->setTimezone( 'Europe/Zurich' );
$DOC->setSourceRootPrefix( '/XSFoundation/include/' );
$DOC->setClassesPrefix( 'XSFoundation/include/XS/Classes/' );
$DOC->setFunctionsPrefix( 'XSFoundation/include/XS/Functions/' );
$DOC->setTypesPrefix( 'XSFoundation/include/XS/XSTypes/' );

print $DOC;

?>
</body>
</html>