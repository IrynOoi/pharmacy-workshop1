-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Aug 02, 2024 at 02:23 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `pharmacy_db`
--

-- --------------------------------------------------------

--
-- Table structure for table `hospital`
--

CREATE TABLE `hospital` (
  `Hospital_ID` char(6) NOT NULL,
  `Hospital_Name` varchar(50) NOT NULL,
  `Hospital_Street` varchar(100) NOT NULL,
  `Hospital_City` varchar(50) NOT NULL,
  `Hospital_State` varchar(50) NOT NULL,
  `Availability` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `hospital`
--

INSERT INTO `hospital` (`Hospital_ID`, `Hospital_Name`, `Hospital_Street`, `Hospital_City`, `Hospital_State`, `Availability`) VALUES
('HS0001', 'Hospital Aman', 'Jalan Petaling', 'Bukit Mertajam', 'Pulau Pinang', 'Available'),
('HS0002', 'Hospital Tuah', 'Jalan Setapak', 'Puching', 'Selangor', 'Available'),
('HS0003', 'Hospital Berasik', 'Jalan Melina', 'Pulau Pinang', 'Perak', 'Available'),
('HS0004', 'Hospital Jebat', 'Jalan Kinabaru', 'Batu Pahat', 'Johor', 'Available'),
('HS0005', 'Hospital Satria', 'Jalan Pemalu', 'Batu Serindam', 'Johor', 'Available'),
('HS0006', 'Hospital Desaru', 'Jalan Desaru', 'Bukit Desaru', 'Pulau Pinang', 'Unavailable'),
('HS0007', 'Hospital Lestari', 'Jalan Peminta', 'Batu Gelugor', 'Pahang', 'Available'),
('HS0008', 'Hospital Kasturi', 'Lorong Damansura', 'Tasik Gula', 'Kelantan', 'Available'),
('HS0009', 'Hospital Lekiri', 'Lorong Pencinta', 'Kubang Bibik', 'Negeri Sembilan', 'Available'),
('HS0010', 'Hospital Lekiu', 'Lorong Sarjana Ria 2', 'Kulai', 'Pahang', 'Available'),
('HS0011', 'Hospital Bahagia', 'Jalan Pelincik 2', 'Ayer Keroh', 'Melaka', 'Available'),
('HS0012', 'Hospital Lestari', 'Jalan Pejuang 1', 'Tasik Gelugor', 'Pulau Pinang', 'Available'),
('HS0013', 'Hospital Kopi', 'Lorong Pancaragam Ria 4', 'Tasik Gula', 'Terengganu', 'Unavailable'),
('HS0014', 'Hospital Nescafe', 'Lorong Kelmarin', 'Kubang Bibik', 'Perlis', 'Available'),
('HS0015', 'Hospital Milo', 'Jalan Sukacita', 'Kubang Semang', 'Pulau Pinang', 'Available'),
('HS0018', 'Hospital Jamaica', 'Jalan Jamaica', 'Bukit Jamaica', 'Pulau Pinang', 'Available'),
('HS0020', 'Hospital Balma', 'Jalan Balma', 'Bukit Balma', 'Pulau Pinang', 'Available'),
('HS0021', 'Hospital Pertama', 'Jalan Pertama', 'Bukit Pertama', 'Pulau Pinang', 'Available');

-- --------------------------------------------------------

--
-- Table structure for table `medication`
--

CREATE TABLE `medication` (
  `Medication_ID` char(6) NOT NULL,
  `Medication_Name` varchar(50) NOT NULL,
  `Medication_Type` varchar(30) NOT NULL,
  `Dosage_Form` varchar(20) NOT NULL,
  `Strength` varchar(20) NOT NULL,
  `Description_text` text DEFAULT NULL,
  `Side_Effects` text DEFAULT NULL,
  `usage_text` text DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `medication`
--

INSERT INTO `medication` (`Medication_ID`, `Medication_Name`, `Medication_Type`, `Dosage_Form`, `Strength`, `Description_text`, `Side_Effects`, `usage_text`) VALUES
('MED001', 'Paracetamol', 'Pain Reliever', 'Tablet', '500mg', 'Used to relieve pain and reduce fever.', 'Nausea, rash', 'Take one tablet every 4-6 hours'),
('MED002', 'Amoxicillin', 'Antibiotic', 'Capsule', '250mg', 'Used to treat bacterial infections.', 'Diarrhea, headache', 'Take one capsule every 8 hours'),
('MED003', 'Vitamin C', 'Vitamin', 'Tablet', '1000mg', 'Used to prevent or treat vitamin C deficiency.', 'Upset stomach', 'Take one tablet daily'),
('MED004', 'Cough Syrup', 'Cough Syrup', 'Syrup', '200mg/5ml', 'Used to relieve cough.', 'Drowsiness, dry mouth', 'Take 5ml every 4-6 hours'),
('MED005', 'Cetirizine', 'Antihistamine', 'Tablet', '10mg', 'Used to treat allergy symptoms.', 'Drowsiness, dry mouth', 'Take one tablet daily'),
('MED006', 'Chlorhexidine', 'Antiseptic', 'Solution', '0.05%', 'Used to disinfect wounds.', 'Skin irritation', 'Apply to the affected area'),
('MED007', 'Ibuprofen', 'Anti-inflammatory', 'Tablet', '400mg', 'Used to reduce inflammation and pain.', 'Nausea, headache', 'Take one tablet every 6-8 hours'),
('MED008', 'Bisacodyl', 'Laxative', 'Tablet', '5mg', 'Used to treat constipation.', 'Abdominal pain, diarrhea', 'Take one tablet at bedtime'),
('MED009', 'Omeprazole', 'Antacid', 'Capsule', '20mg', 'Used to treat acid reflux.', 'Headache, stomach pain', 'Take one capsule daily'),
('MED010', 'Loratadine', 'Allergy Relief', 'Tablet', '10mg', 'Used to treat allergy symptoms.', 'Drowsiness, dry mouth', 'Take one tablet daily'),
('MED011', 'Metformin', 'Antidiabetic', 'Tablet', '500mg', 'Used to control blood sugar levels in type 2 diabetes.', 'Gastrointestinal upset', 'Take one tablet twice daily'),
('MED012', 'Losartan', 'Antihypertensive', 'Tablet', '50mg', 'Used to treat high blood pressure.', 'Dizziness, headache', 'Take one tablet daily'),
('MED013', 'Simvastatin', 'Cholesterol-lowering', 'Tablet', '20mg', 'Used to lower cholesterol levels.', 'Muscle pain, digestive issues', 'Take one tablet in the evening'),
('MED014', 'Aspirin', 'Pain Reliever', 'Tablet', '81mg', 'Used to reduce the risk of heart attack.', 'Upset stomach, bleeding', 'Take one tablet daily'),
('MED015', 'Hydrochlorothiazide', 'Diuretic', 'Tablet', '25mg', 'Used to treat high blood pressure and fluid retention.', 'Dizziness, dehydration', 'Take one tablet daily');

-- --------------------------------------------------------

--
-- Table structure for table `medication_stock`
--

CREATE TABLE `medication_stock` (
  `Stock_ID` char(6) NOT NULL,
  `Stock_Category` varchar(20) NOT NULL,
  `Stock_Volume` int(5) NOT NULL,
  `Stock_Quantity` int(5) NOT NULL,
  `Total_Stock_Volume` int(11) DEFAULT NULL,
  `Staff_ID` char(6) NOT NULL,
  `Medication_ID` char(6) NOT NULL,
  `Status` varchar(11) NOT NULL,
  `Storage_Conditions` text NOT NULL,
  `Expiry_Date` date NOT NULL,
  `Supplier_ID` char(6) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `medication_stock`
--

INSERT INTO `medication_stock` (`Stock_ID`, `Stock_Category`, `Stock_Volume`, `Stock_Quantity`, `Total_Stock_Volume`, `Staff_ID`, `Medication_ID`, `Status`, `Storage_Conditions`, `Expiry_Date`, `Supplier_ID`) VALUES
('SK001', 'Pain Reliever', 500, 10, 5000, 'ST0001', 'MED001', 'Available', 'Store in a cool, dry place', '2025-12-31', 'SUP001'),
('SK002', 'Antibiotic', 250, 15, 3750, 'ST0002', 'MED002', 'Available', 'Store in a cool, dry place', '2024-11-30', 'SUP001'),
('SK003', 'Vitamin', 100, 30, 3000, 'ST0003', 'MED003', 'Available', 'Store at room temperature', '2026-01-15', 'SUP002'),
('SK004', 'Cough Syrup', 200, 20, 4000, 'ST0004', 'MED004', 'Available', 'Store at room temperature', '2025-10-30', 'SUP002'),
('SK005', 'Antihistamine', 150, 25, 3750, 'ST0005', 'MED005', 'Available', 'Store at room temperature', '2025-08-15', 'SUP003'),
('SK006', 'Antiseptic', 300, 12, 3600, 'ST0006', 'MED006', 'Available', 'Store at room temperature', '2026-01-20', 'SUP003'),
('SK007', 'Anti-inflammatory', 400, 10, 4000, 'ST0007', 'MED007', 'Available', 'Store at room temperature', '2024-12-31', 'SUP004'),
('SK008', 'Laxative', 250, 18, 4500, 'ST0008', 'MED008', 'Available', 'Store at room temperature', '2025-07-20', 'SUP004'),
('SK009', 'Antacid', 350, 22, 7700, 'ST0009', 'MED009', 'Available', 'Store at room temperature', '2025-11-15', 'SUP005'),
('SK010', 'Allergy Relief', 450, 14, 6300, 'ST0010', 'MED010', 'Available', 'Store at room temperature', '2025-09-10', 'SUP005');

-- --------------------------------------------------------

--
-- Table structure for table `medication_transaction`
--

CREATE TABLE `medication_transaction` (
  `Transaction_ID` char(6) NOT NULL,
  `Transaction_Date` date NOT NULL,
  `Medication_ID` char(6) NOT NULL,
  `Quantity` int(5) NOT NULL,
  `Patient_ID` char(6) NOT NULL,
  `Status` varchar(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `medication_transaction`
--

INSERT INTO `medication_transaction` (`Transaction_ID`, `Transaction_Date`, `Medication_ID`, `Quantity`, `Patient_ID`, `Status`) VALUES
('TX0001', '2023-01-15', 'MED001', 5, 'PT0001', 'Completed'),
('TX0002', '2023-01-16', 'MED002', 2, 'PT0002', 'Completed'),
('TX0003', '2023-01-17', 'MED003', 3, 'PT0003', 'Pending'),
('TX0004', '2023-01-18', 'MED004', 4, 'PT0004', 'Completed'),
('TX0005', '2023-01-19', 'MED005', 1, 'PT0005', 'Cancelled'),
('TX0006', '2023-01-20', 'MED006', 7, 'PT0006', 'Completed'),
('TX0007', '2023-01-21', 'MED007', 6, 'PT0007', 'Completed'),
('TX0008', '2023-01-22', 'MED008', 2, 'PT0008', 'Pending'),
('TX0009', '2023-01-23', 'MED009', 8, 'PT0009', 'Completed'),
('TX0010', '2023-01-24', 'MED010', 3, 'PT0010', 'Completed'),
('TX0011', '2023-01-25', 'MED011', 4, 'PT0011', 'Completed'),
('TX0012', '2023-01-26', 'MED012', 5, 'PT0012', 'Completed'),
('TX0013', '2023-01-27', 'MED013', 2, 'PT0013', 'Pending'),
('TX0014', '2023-01-28', 'MED014', 9, 'PT0014', 'Completed'),
('TX0015', '2023-01-29', 'MED015', 1, 'PT0015', 'Completed');

-- --------------------------------------------------------

--
-- Table structure for table `patient`
--

CREATE TABLE `patient` (
  `Patient_ID` char(6) NOT NULL,
  `Patient_Name` varchar(50) NOT NULL,
  `Patient_Gender` char(1) NOT NULL,
  `Patient_Age` int(2) NOT NULL,
  `Patient_DOB` date NOT NULL,
  `Patient_Address` varchar(100) NOT NULL,
  `Patient_Height` double NOT NULL,
  `Patient_Weight` double NOT NULL,
  `Patient_TelNo` varchar(14) NOT NULL,
  `Patient_Email` varchar(50) DEFAULT NULL,
  `Medical_History` text DEFAULT NULL,
  `Active_Status` varchar(8) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `patient`
--

INSERT INTO `patient` (`Patient_ID`, `Patient_Name`, `Patient_Gender`, `Patient_Age`, `Patient_DOB`, `Patient_Address`, `Patient_Height`, `Patient_Weight`, `Patient_TelNo`, `Patient_Email`, `Medical_History`, `Active_Status`) VALUES
('PT0001', 'Gary Kim Jung En', 'M', 23, '2000-01-15', '4A, Jalan Bintulu', 175.4, 56.2, '011-23678821', 'garykim@example.com', 'No significant history', 'Active'),
('PT0002', 'Sandra A/P Kumaran', 'F', 20, '2001-03-20', 'B-G-03, Lorong Saujana Aman 9, Taman Kelmarin', 160.3, 59.35, '010-8654093', 'sandra@example.com', 'No significant history', 'Active'),
('PT0003', 'Melissa Tang Yi Xin', 'F', 32, '1990-01-02', '102, Pearl Drive Morgantown', 163.2, 45.2, '011-09074237', 'melissa@example.com', 'Hypertension', 'Active'),
('PT0004', 'Macaurel Noel', 'M', 26, '1995-12-13', 'Jln Bintulu, Taman Bintulu, 14300, Bukit Binatulu', 174.3, 63.2, '017-33456672', 'macaurel@example.com', 'Diabetes', 'Active'),
('PT0005', 'Siti Zahara binti Ab', 'F', 22, '1999-07-12', '2A, Jalan Bintulu, Taman Bintulu, 23450, Sabah', 163.2, 49.9, '017-35678832', 'siti@example.com', 'No significant history', 'Active'),
('PT0006', 'Zulkarnain Bin Razak', 'M', 30, '1992-07-03', '3A, Jalan Mutiara, Taman Mutiara Ria', 175.4, 63.2, '017-8825336', 'zulkarnain@example.com', 'Asthma', 'Active'),
('PT0007', 'Melissa Lim', 'F', 28, '1994-07-08', '108, Jalan Damansara, Taman Damansara', 165.4, 45.5, '012-3344778', 'melissa.lim@example.com', 'Allergy', 'Active'),
('PT0008', 'Muhamed Syaqirin Zul', 'M', 35, '1987-01-23', '7G-34, Jalan 2/3, PJS72M, 23986 Bukit Payong', 176.2, 63.3, '019-3768823', 'muhamed@example.com', 'No significant history', 'Active'),
('PT0009', 'Liew Kai Tian', 'M', 27, '1995-11-28', 'P-81-76, Jln 94Z, Taman Selatan, 02621 Puching', 169.2, 64.6, '05-8004605', 'liew@example.com', 'No significant history', 'Active'),
('PT0010', 'Chung Hok Gong', 'M', 31, '1991-06-25', '2, Lorong Wan Kadir 6/47, 23215 Melaka', 162.5, 60.8, '017-3838446', 'chung@example.com', 'Chronic Migraine', 'Active'),
('PT0011', 'Rueben a/l Sivakumar', 'M', 29, '1993-03-18', '37, Jalan Robson, Batu Sg.Buaya, 52778 Tambun', 178.9, 67.4, '015-5444310', 'rueben@example.com', 'No significant history', 'Active'),
('PT0012', 'Nurfadlhlin binti Hananie', 'F', 27, '1995-09-23', '2, Lorong Wan Kadir 6/47, 23215 Sg.Petani', 161.4, 46.3, '03-88569242', 'nurfadlhlin@example.com', 'No significant history', 'Active'),
('PT0013', 'Kar Dong Pom', 'M', 42, '1980-04-08', '37, Jln Robson, Bt.Buaya, 52778 Tambin', 164.1, 47.2, '05-3066929', 'kar@example.com', 'High Cholesterol', 'Active'),
('PT0014', 'R.S. Vengatarakoo', 'F', 20, '2002-05-02', '56, Jalan SS9, 59956 Taman U-Thant, Kuala Lumpur', 173.8, 63.9, '016-5722957', 'rs@example.com', 'No significant history', 'Active'),
('PT0015', 'Alex Chua Wok Gao', 'M', 35, '1987-02-16', '1, Jalan 7/12, Batu Melawati, 46889 Semang', 165.8, 60.9, '015-6172561', 'alex@example.com', 'No significant history', 'Active'),
('PT0016', 'Insyirah binti Zarith', 'F', 25, '1997-06-18', '2, Jln 22I, USJ 8, 16052 Pasir Mas, Kelantan', 158.3, 44.8, '06-23804093', 'insyirah@example.com', 'Thyroid Issues', 'Active'),
('PT0017', 'Cheng Shim Kua', 'F', 54, '1968-01-24', '34, Jalan Utama 3/4Z, 21836 Bukit Anggerik', 165.3, 51.9, '012-0778673', 'cheng@example.com', 'No significant history', 'Active'),
('PT0018', 'Chou Ho Koong', 'M', 28, '1994-12-03', 'No. 9, Lorong 7P, Kondominium Angkasa, 94832 Bario', 167.5, 67.9, '012-8901852', 'chou@example.com', 'No significant history', 'Active'),
('PT0019', 'Nik Azril bin Syed Zaif', 'M', 46, '1976-11-27', '3, Jln 78O, Tmn Desa Pinang, 73009 Bagan', 171.2, 60.5, '019-8446560', 'nik@example.com', 'Diabetes', 'Active'),
('PT0020', 'Rani Sinnandavar', 'F', 29, '1993-04-16', 'No. 9, Lorong Raja Abdullah 2/9, Bandar Sri Rahman', 166.3, 49.5, '014-5929514', 'rani@example.com', 'No significant history', 'Active'),
('PT0021', 'Stella Goh Lein Bik', 'F', 49, '1973-03-17', 'Lot 30, Jln Zainal Abidin 64C, Kampung Bahagia', 163.8, 47.9, '019-6335372', 'stella@example.com', 'Hypertension', 'Active'),
('PT0022', 'Mohamad Latiff bin Mokhtar', 'M', 52, '1970-11-09', 'No. 42, Jln Chow Kit 8, Sri Pertama, 17488 Bt.Kawa', 172.4, 67.1, '018-4295194', 'mohamad@example.com', 'No significant history', 'Active'),
('PT0023', 'Mohammed Haji Radin Nazri bin Fauzi', 'M', 41, '1981-09-15', '1, Jalan SS2, 12219 George Town, Pulau Pinang', 174.2, 64.9, '012-9360791', 'mohammed@example.com', 'No significant history', 'Active'),
('PT0024', 'Chou Ho Li', 'F', 26, '1996-07-18', 'Taman Jaya, 62340 Precinct 16, Putrajaya', 163.8, 46.4, '011-12467165', 'chouli@example.com', 'No significant history', 'Active'),
('PT0025', 'Paramjit a/l Palanivel Puspanathan', 'M', 23, '1999-08-09', 'No.49, Jln Dato Abdul Rahman 12897 Pdg.Besar', 179.3, 64.9, '017-7331579', 'paramjit@example.com', 'No significant history', 'Inactive'),
('PT0026', 'Ng', 'M', 21, '2001-08-08', 'Jalan Binjai', 170.2, 55.6, '012-6678954', 'ng@example.com', 'No significant history', 'Active'),
('PT0027', 'Liew', 'M', 28, '1994-04-12', '28, Jalan Bintang Meriah', 166.3, 56.8, '017-87458862', 'liew@example.com', 'No significant history', 'Active'),
('PT0029', 'Tan', 'M', 25, '1998-07-06', 'Jalan Bentulu', 175.8, 64, '017-88453395', 'tan@example.com', 'No significant history', 'Active'),
('PT0046', 'Tan Chee Meng', 'M', 24, '1999-06-05', 'Jalan Bentulu 35', 175.6, 58, '017-8903456', 'tan.chee.meng@example.com', 'No significant history', 'Active'),
('PT0050', 'Mei Mei', 'F', 23, '2000-01-01', 'SECRET', 170, 60, '01101110112', 'mei.mei@example.com', 'No significant history', 'Active'),
('PT0055', 'Xi Gou', 'M', 22, '2000-12-31', 'Secret', 200, 100, '01110101110', 'xi.gou@example.com', 'No significant history', 'Active'),
('PT0135', 'Lim', 'M', 26, '1997-08-09', 'Jalan Bentar', 176.5, 58, '017-5869363', 'lim@example.com', 'No significant history', 'Active');

-- --------------------------------------------------------

--
-- Table structure for table `patient_record`
--

CREATE TABLE `patient_record` (
  `Record_ID` char(6) NOT NULL,
  `Hospital_ID` char(6) NOT NULL,
  `Patient_ID` char(6) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `patient_record`
--

INSERT INTO `patient_record` (`Record_ID`, `Hospital_ID`, `Patient_ID`) VALUES
('PR0001', 'HS0002', 'PT0003'),
('PR0002', 'HS0001', 'PT0002'),
('PR0003', 'HS0004', 'PT0001'),
('PR0004', 'HS0011', 'PT0002'),
('PR0005', 'HS0003', 'PT0004'),
('PR0006', 'HS0007', 'PT0005'),
('PR0007', 'HS0006', 'PT0007'),
('PR0008', 'HS0004', 'PT0010'),
('PR0009', 'HS0008', 'PT0006'),
('PR0010', 'HS0005', 'PT0007'),
('PR0011', 'HS0007', 'PT0010'),
('PR0012', 'HS0009', 'PT0009'),
('PR0013', 'HS0006', 'PT0005'),
('PR0014', 'HS0005', 'PT0006'),
('PR0015', 'HS0007', 'PT0002');

-- --------------------------------------------------------

--
-- Table structure for table `staff`
--

CREATE TABLE `staff` (
  `Staff_ID` char(6) NOT NULL,
  `Staff_Name` varchar(100) DEFAULT NULL,
  `Staff_Gender` char(1) NOT NULL,
  `Staff_Age` int(3) NOT NULL,
  `Staff_Address` varchar(100) NOT NULL,
  `Staff_Telno` varchar(15) NOT NULL,
  `Staff_Position` varchar(30) NOT NULL,
  `Staff_Password` varchar(60) NOT NULL,
  `Admin_ID` char(6) DEFAULT NULL,
  `Active_Status` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `staff`
--

INSERT INTO `staff` (`Staff_ID`, `Staff_Name`, `Staff_Gender`, `Staff_Age`, `Staff_Address`, `Staff_Telno`, `Staff_Position`, `Staff_Password`, `Admin_ID`, `Active_Status`) VALUES
('ST0001', 'BOO JIA JUN', 'M', 25, '13, Jalan Melanor, Taman Mentor, 73500 Petiling', '017-4702345', 'Pharmacist', '9a5a41279a48606bca05e2fba2b2352836ce976b', 'ST0001', 'Active'),
('ST0002', 'CHAI YI JING', 'F', 29, '18 Jalan Melati, Kota Kinabalu', '011-41238846', 'Pharmacist', '40bd001563085fc35165329ea1ff5c5ecbdbbeef', 'ST0002', 'Active'),
('ST0003', 'NURUL IZZATI BINTI ABDUL RAZAK', 'F', 26, '22 Jalan Melaju, Puchong, Selangor', '018-4076582', 'Pharmacy Assistant', '1daed09770e3796c1d6df015f6d4eaaca35d01e4', 'ST0003', 'Active'),
('ST0004', 'AQILAH', 'F', 28, '3B, Jalan Bukit Bintang, Taman Binatang', '017-4356782', 'Pharmacy Assistant', '780b39fc1838ec9fd5a6507d62c0fda88b2e9f83', 'ST0002', 'Active'),
('ST0005', 'OOI XIEN XIEN', 'F', 25, '3A, Jalan Bintang, Taman Udang, Bukit Udang', '017-5867363', 'Pharmacy Assistant', '477333017ac7958ab5c0215ec528bde422369527', 'ST0002', 'Active'),
('ST0006', 'TEE YONG JIAN', 'M', 32, '45, Lorong Sarjana, Taman Sarjana, Pulau Pinang', '012-65478823', 'Pharmacist', 'd71e9fd5049266173b59c678a9e7b80165f6e46e', 'ST0003', 'Active'),
('ST0007', 'AMANDA VERA YAPP', 'F', 34, 'L22 Bangunan Abdullah, Jln Melaka, Kuala Lumpur', '07-12350543', 'Pharmacist', 'f71667b55f0b2b907c7bc79ecbb94a0937d0f6d2', 'ST0001', 'Active'),
('ST0008', 'ENGKU AMIR LUTFI BIN ENGKU ZAIN', 'M', 29, '31A Jalan Laksamana 6, Taman Mewah Jaya, Klang', '011-51626857', 'Staff', '311e1bbe1e9fbda18fcd0e91bf3014d9d5749059', 'ST0002', 'Active'),
('ST0009', 'HARIS A/L R SURESH', 'M', 35, '764, Jalan Subang 4, Taman Perindustrian', '03-26924094', 'Staff', '66d7f53a4a7fae3d93e7986138895727ab414d3e', 'ST0002', 'Active'),
('ST0010', 'MUHAMMAD AMIERUL BIN CHE WAN MOHD YAZID', 'M', 43, '48, Jalan Mohana Chandran 60V, PJS9, 95380 Lawas', '011-32541158', 'Pharmacy Assistant', '4d31653f7e0db8324e33960300adf146a913cdaa', 'ST0001', 'Active'),
('ST0011', 'NUR ALIA MUNIRAH BINTI ABD RAHIM', 'F', 31, 'No. L-77-94, Jalan 8, 20711 Chukai, Terengganu', '015-4874820', 'Staff', '3a823e71995cc36e559c7b9b9de07337c8df66aa', 'ST0003', 'Active'),
('ST0012', 'NURAIN ZAHIDAH BINTI MOHD YUSOF', 'F', 24, 'Lot T-72-63, Lorong 78R, Batu Selamat', '09-4100423', 'Pharmacist', 'dcc6a426f15c177d46e342a25afcbf27e53a25d9', 'ST0001', 'Active'),
('ST0013', 'SHOMESWARAN A/L MUGUNTHAN', 'M', 26, '78, Jalan Pantai Baharu, PJS49A, 62078 Precinct 16', '07-2995872', 'Pharmacy Assistant', '6ee2bdeabf30bcf51ca80bb6efbe63f9bb72a116', 'ST0002', 'Active'),
('ST0014', 'AIDA', 'F', 33, '8-6, Jalan Kuala Kangsar 4/65, Bandar Pahlawan', '015-3300466', 'Staff', '695860dd65a674d73c57409e58031a0a9798c9ac', 'ST0001', 'Active'),
('ST0015', 'TAN LE XIONG', 'M', 26, '7, Jalan 9, PJU33, 76245 Batu Berendam, Melaka', '09-4100423', 'Pharmacist', '6745d0e432da6374b0856dd7cd337471cb13797f', 'ST0001', 'Active'),
('ST0016', 'PAVITHRAN A/L KANAPATHY', 'M', 42, 'No.W-79-44, Jln 4, Apartment Setia Jaya', '015-4227344', 'Staff', '3287e82482416c175d1233176879d88f0756eaaf', 'ST0001', 'Active'),
('ST0017', 'ZURINE AISHAH BINTI ZULKIFLI', 'F', 40, '102, Jalan Selamat 24J, 67866, Bandar Keramat', '09-4100423', 'Pharmacist', '0f61ce2d215a588ffd94a211586b8a4f3744f903', 'ST0002', 'Active'),
('ST0020', 'WAN MOHAMMAD ZAMAN AZ ZIKRY BIN ZAINUDDIN', 'M', 28, 'Jalan Binjai', '017-223345', 'Staff', '8cb2237d0679ca88db6464eac60da96345513964', 'ST0001', 'Active'),
('ST0030', 'SITI ZULAIKHA BINTI MOHD NIZAM', 'F', 18, 'Secret', '01101110111', 'Pharmacist', '6b5d07758a08dbf86e91b837b74a1b9e655f3513', 'ST0001', 'Active'),
('ST0041', 'SITI BALQIS BINTI MAT MUHARAM', 'F', 21, 'Secret', '01101010101', 'Pharmacy Assistant', '762a7911a163d856ceb1f08d8012946de2df2032', 'ST0001', 'Active'),
('ST0135', 'TANG', 'M', 31, 'Jalan Bintulu', '017-5867343', 'Pharmacist', '6367c48dd193d56ea7b0baad25b19455e529f5ee', 'ST0004', 'Active'),
('ST0456', 'NG WEI HEN', 'M', 26, 'Jalan Bantai', '019-3345667', 'Staff', '6367c48dd193d56ea7b0baad25b19455e529f5ee', 'ST0006', 'Inactive');

-- --------------------------------------------------------

--
-- Table structure for table `staff_record`
--

CREATE TABLE `staff_record` (
  `Staff_ID` char(6) NOT NULL,
  `Hospital_ID` char(6) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `staff_record`
--

INSERT INTO `staff_record` (`Staff_ID`, `Hospital_ID`) VALUES
('ST0001', 'HS0001'),
('ST0002', 'HS0002'),
('ST0003', 'HS0003'),
('ST0004', 'HS0004'),
('ST0005', 'HS0005'),
('ST0006', 'HS0006'),
('ST0007', 'HS0007'),
('ST0008', 'HS0008'),
('ST0009', 'HS0009'),
('ST0010', 'HS0010'),
('ST0011', 'HS0011'),
('ST0012', 'HS0012'),
('ST0013', 'HS0013'),
('ST0014', 'HS0014'),
('ST0015', 'HS0015'),
('ST0135', 'HS0018'),
('ST0456', 'HS0020');

-- --------------------------------------------------------

--
-- Table structure for table `supplier`
--

CREATE TABLE `supplier` (
  `Supplier_ID` char(6) NOT NULL,
  `Supplier_Name` varchar(100) NOT NULL,
  `Contact_Number` varchar(15) NOT NULL,
  `Address` varchar(255) NOT NULL,
  `Email` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `supplier`
--

INSERT INTO `supplier` (`Supplier_ID`, `Supplier_Name`, `Contact_Number`, `Address`, `Email`) VALUES
('SUP001', 'Pharma Supplies Inc.', '123-456-7890', 'No 1, Jalan UTeM, Taman Melaka Baru, Melaka', 'contact@pharmasupplies.com'),
('SUP002', 'HealthCo Ltd.', '987-654-3210', 'No 2, Jalan Kampung Pantai, 75450 Melaka', 'info@healthco.com'),
('SUP003', 'Wellness Partners', '555-123-4567', 'No 3, Jalan Industri, 76100 Melaka', 'support@wellnesspartners.com'),
('SUP004', 'MediCare Solutions', '321-654-9870', 'No 4, Jalan UTeM 2, Taman Melaka Jaya, Melaka', 'service@medicaresolutions.com'),
('SUP005', 'BioPharma Ltd.', '654-321-0987', 'No 5, Jalan Bukit Beruang, 76100 Melaka', 'contact@biopharma.com');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `hospital`
--
ALTER TABLE `hospital`
  ADD PRIMARY KEY (`Hospital_ID`);

--
-- Indexes for table `medication`
--
ALTER TABLE `medication`
  ADD PRIMARY KEY (`Medication_ID`);

--
-- Indexes for table `medication_stock`
--
ALTER TABLE `medication_stock`
  ADD PRIMARY KEY (`Stock_ID`),
  ADD KEY `Staff_ID` (`Staff_ID`),
  ADD KEY `Medication_ID` (`Medication_ID`),
  ADD KEY `Supplier_ID` (`Supplier_ID`);

--
-- Indexes for table `medication_transaction`
--
ALTER TABLE `medication_transaction`
  ADD PRIMARY KEY (`Transaction_ID`),
  ADD KEY `Medication_ID` (`Medication_ID`),
  ADD KEY `Patient_ID` (`Patient_ID`);

--
-- Indexes for table `patient`
--
ALTER TABLE `patient`
  ADD PRIMARY KEY (`Patient_ID`);

--
-- Indexes for table `patient_record`
--
ALTER TABLE `patient_record`
  ADD PRIMARY KEY (`Record_ID`,`Hospital_ID`,`Patient_ID`),
  ADD KEY `Hospital_ID` (`Hospital_ID`),
  ADD KEY `Patient_ID` (`Patient_ID`);

--
-- Indexes for table `staff`
--
ALTER TABLE `staff`
  ADD PRIMARY KEY (`Staff_ID`);

--
-- Indexes for table `staff_record`
--
ALTER TABLE `staff_record`
  ADD PRIMARY KEY (`Staff_ID`,`Hospital_ID`),
  ADD KEY `Hospital_ID` (`Hospital_ID`);

--
-- Indexes for table `supplier`
--
ALTER TABLE `supplier`
  ADD PRIMARY KEY (`Supplier_ID`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `medication_stock`
--
ALTER TABLE `medication_stock`
  ADD CONSTRAINT `medication_stock_ibfk_1` FOREIGN KEY (`Staff_ID`) REFERENCES `staff` (`Staff_ID`),
  ADD CONSTRAINT `medication_stock_ibfk_2` FOREIGN KEY (`Medication_ID`) REFERENCES `medication` (`Medication_ID`),
  ADD CONSTRAINT `medication_stock_ibfk_3` FOREIGN KEY (`Supplier_ID`) REFERENCES `supplier` (`Supplier_ID`);

--
-- Constraints for table `medication_transaction`
--
ALTER TABLE `medication_transaction`
  ADD CONSTRAINT `medication_transaction_ibfk_1` FOREIGN KEY (`Medication_ID`) REFERENCES `medication` (`Medication_ID`),
  ADD CONSTRAINT `medication_transaction_ibfk_2` FOREIGN KEY (`Patient_ID`) REFERENCES `patient` (`Patient_ID`);

--
-- Constraints for table `patient_record`
--
ALTER TABLE `patient_record`
  ADD CONSTRAINT `patient_record_ibfk_1` FOREIGN KEY (`Hospital_ID`) REFERENCES `hospital` (`Hospital_ID`),
  ADD CONSTRAINT `patient_record_ibfk_2` FOREIGN KEY (`Patient_ID`) REFERENCES `patient` (`Patient_ID`);

--
-- Constraints for table `staff_record`
--
ALTER TABLE `staff_record`
  ADD CONSTRAINT `staff_record_ibfk_1` FOREIGN KEY (`Staff_ID`) REFERENCES `staff` (`Staff_ID`),
  ADD CONSTRAINT `staff_record_ibfk_2` FOREIGN KEY (`Hospital_ID`) REFERENCES `hospital` (`Hospital_ID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
