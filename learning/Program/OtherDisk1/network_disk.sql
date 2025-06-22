-- MySQL dump 10.13  Distrib 5.7.33, for Linux (x86_64)
--
-- Host: localhost    Database: network_disk
-- ------------------------------------------------------
-- Server version	5.7.33-0ubuntu0.18.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `userinfo`
--

DROP TABLE IF EXISTS `userinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `userinfo` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(20) DEFAULT NULL,
  `salt` char(16) DEFAULT NULL,
  `cryptpasswd` varchar(128) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `userinfo`
--

LOCK TABLES `userinfo` WRITE;
/*!40000 ALTER TABLE `userinfo` DISABLE KEYS */;
INSERT INTO `userinfo` VALUES (1,'root','',''),(2,'A','$6$q3UZ4lvZ','$6$q3UZ4lvZ$WeYnU2BbnXQraE1WMfHmkBowXw1DRB.nPan96viwmBQOXo.hiAgbcCiRDOjiu.4dWmt7EinV0Xr4ZiJnKaTzQ1'),(3,'B','$6$ouw7Mqfq','$6$ouw7Mqfq$uNvUo.MoUKkyDXCswygALuCVhbrfDiMZkW414OThK/dVxAH1FgGcZR1aVy/MyV8.3BDEU5kRrVNWHQRYVAn62.'),(4,'C','$6$KfFeorwh','$6$KfFeorwh$qJR7GuVDBHfdauR2YHGFHw4h2wwnF87gUNdSKQC6ehPYK2GqIBbHlRY85DZqNfrkYqMD.ufWF5y2YEQTCBHQg1'),(5,'D','$6$HO85D33a','$6$HO85D33a$rAQkuyc.DYn4pGUYg8h84DHYD.M8s3ZbBkyAnJdCnHCH4yyd5JG7eyF3vfGUILSutlnIHQxLmZmouMQhGXM4d.'),(6,'E','$6$8W73k605','$6$8W73k605$hj2dzDxgwhR67kPcozDKpYlm3O2N2Ip95AwBl4R.RJLetWR4VS7RfmhDdkfMWDB3/VJVHOfYNrBJeAMUwJgjQ.'),(7,'F','$6$A9Hwf60b','$6$A9Hwf60b$AbcZqszOzlYzh8.jcO.BrwF0g9CIh/cpR7lvcQXcpJ5B/wHR1.Nu1EdMpHwWxeMn3SyHfpJErXqg4w9AIRCe9.'),(8,'G','$6$4I2C603G','$6$4I2C603G$ROyAX.vx3DVcrcQTsI2yxelZF6B4mzdiviGcXBsgUVD7AvASNfKnSeoq1z4.kQ05.Cz493yORDSBgHMBR6HL00'),(9,'H','$6$pgDBiBkn','$6$pgDBiBkn$YSQ9bYte07rtunCDuUxTfdwbo3kf9VXLJpP4XiRePBIsbYqkvy6kM8ge9IiyU7Xx4iANPNnIDL..eFdp7Ecl./');
/*!40000 ALTER TABLE `userinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `virtual_file`
--

DROP TABLE IF EXISTS `virtual_file`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `virtual_file` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `filename` varchar(32) DEFAULT NULL,
  `parent_id` int(11) DEFAULT NULL,
  `owner_id` int(11) DEFAULT NULL,
  `type` char(1) DEFAULT NULL,
  `filesize` int(11) DEFAULT NULL,
  `md5` varchar(128) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `owner_id` (`owner_id`),
  CONSTRAINT `virtual_file_ibfk_1` FOREIGN KEY (`owner_id`) REFERENCES `userinfo` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `virtual_file`
--

LOCK TABLES `virtual_file` WRITE;
/*!40000 ALTER TABLE `virtual_file` DISABLE KEYS */;
INSERT INTO `virtual_file` VALUES (1,'root',0,1,'d',0,'0'),(2,'A',1,2,'d',0,'0'),(3,'B',1,3,'d',0,'0'),(4,'movie',2,2,'d',0,'0'),(5,'music',2,2,'d',0,'0'),(6,'love.mp4',4,2,'f',12,'b7b68f757050671705a01e6c6bbcd719'),(7,'book',2,2,'d',0,'0'),(8,'txt',2,2,'d',0,'0'),(9,'delete',2,2,'d',0,'0'),(10,'love.mp4',2,2,'f',12,'b7b68f757050671705a01e6c6bbcd719'),(15,'sing.mp3',2,2,'f',5,'450e8f77deb73588265793e4cc8cecdc'),(16,'H',1,9,'d',0,'0');
/*!40000 ALTER TABLE `virtual_file` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-05-11 14:18:58
