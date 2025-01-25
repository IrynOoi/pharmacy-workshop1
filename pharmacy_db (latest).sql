-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 22, 2025 at 10:18 AM
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
  `Hospital_ID` int(10) UNSIGNED NOT NULL,
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
(2, 'Hospital Tuah', 'Jalan Setapak', 'Puching', 'Selangor', 'Available'),
(3, 'Hospital Geral', 'Jalan Bari', 'Ayer Keroh', 'Melaka', 'Available'),
(4, 'Hospital Jebat', 'Jalan Kinabaru', 'Bukit Kenangan', 'Johor', 'Available'),
(5, 'Hospital Satria', 'Jalan Pemalu', 'Batu Serindam', 'Johor', 'Available'),
(6, 'Hospital Desaru', 'Jalan Desaru', 'Bukit Desaru', 'Pulau Pinang', 'Available'),
(7, 'Hospital Lestari', 'Jalan Peminta', 'Batu Gelugor', 'Pahang', 'Available'),
(8, 'Hospital Kasturi', 'Lorong Damansura', 'Tasik Gula', 'Kelantan', 'Available'),
(9, 'Hospital Lekir', 'Lorong Pencinta', 'Kubang Bibik', 'Negeri Sembilan', 'Available'),
(10, 'Hospital Lekiu', 'Lorong Sarjana Ria 2', 'Kulai', 'Pahang', 'Available'),
(11, 'Hospital Bahagia', 'Jalan Pelincik 2', 'Ayer Keroh', 'Melaka', 'Available'),
(12, 'Hospital Lestari', 'Jalan Pejuang 1', 'Tasik Gelugor', 'Pulau Pinang', 'Available'),
(13, 'Hospital Kopi', 'Lorong Pancaragam Ria 4', 'Tasik Gula', 'Terengganu', 'Unavailable'),
(14, 'Hospital Nescafe', 'Lorong Kelmarin', 'Kubang Bibik', 'Perlis', 'Available'),
(15, 'Hospital Milo', 'Jalan Sukacita', 'Kubang Semang', 'Pulau Pinang', 'Available'),
(16, 'Hospital Jamaica', 'Jalan Jamaica', 'Bukit Jamaica', 'Pulau Pinang', 'Available'),
(17, 'Hospital Balma', 'Jalan Balma', 'Bukit Balma', 'Pulau Pinang', 'Available'),
(18, 'Hospital Pertama', 'Jalan Pertama', 'Bukit Pertama', 'Pulau Pinang', 'Available'),
(20, 'hospital hello', 'jalan keris', 'jfnaj', 'johor', 'Available'),
(22, 'hospital putih', 'jalan yakya awal', 'johor', 'johor', 'Available'),
(23, 'hospital hai', 'jalan oo', 'bukit tambun', 'johor', 'Available'),
(24, 'HOSPITAL TUN AMINAH', 'Jalan keris', 'Batu Pahat', 'Johor', 'Available'),
(25, 'Hopital Lewat', 'Jalan Keris 25', 'Batu Pahat', 'Johor', 'Available');

-- --------------------------------------------------------

--
-- Table structure for table `medication`
--

CREATE TABLE `medication` (
  `Medication_ID` int(10) UNSIGNED NOT NULL,
  `Medication_Name` varchar(50) NOT NULL,
  `Medication_Type` varchar(30) NOT NULL,
  `Dosage_Form` varchar(20) NOT NULL,
  `Strength` varchar(20) NOT NULL,
  `Description_text` text DEFAULT NULL,
  `Side_Effects` text DEFAULT NULL,
  `usage_text` text DEFAULT NULL,
  `Price` decimal(10,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `medication`
--

INSERT INTO `medication` (`Medication_ID`, `Medication_Name`, `Medication_Type`, `Dosage_Form`, `Strength`, `Description_text`, `Side_Effects`, `usage_text`, `Price`) VALUES
(1, 'paracetamol', 'Pain killer', 'tablet', '500mg', 'Used to relieve pain and reduce fever.', 'nausea', 'Take One tablet every 4-6 hours', 12.00),
(2, 'Panadol', 'Antibiotic', 'Capsule', '250mg', 'Used to treat bacterial infections.', 'Diarrhea, headache', 'Take one capsule every 8 hours', 15.50),
(4, 'Cough Syrup', 'Cough Syrup', 'Syrup', '200mg/5ml', 'Used to relieve cough.', 'Drowsiness, dry mouth', 'Take 5ml every 4-6 hours', 12.00),
(5, 'Cetirizine', 'Antihistamine', 'Tablet', '10mg', 'Used to treat allergy symptoms.', 'Drowsiness, dry mouth', 'Take one tablet daily', 7.25),
(6, 'Chlorhexidine', 'Antiseptic', 'Solution', '0.05%', 'Used to disinfect wounds.', 'Skin irritation', 'Apply to the affected area', 5.00),
(7, 'Ibuprofen', 'Anti-inflammatory', 'Tablet', '400mg', 'Used to reduce inflammation and pain.', 'Nausea, headache', 'Take one tablet every 6-8 hours', 11.00),
(8, 'Bisacodyl', 'Laxative', 'Tablet', '5mg', 'Used to treat constipation.', 'Abdominal pain, diarrhea', 'Take one tablet at bedtime', 6.50),
(9, 'Omeprazole', 'Antacid', 'Capsule', '20mg', 'Used to treat acid reflux.', 'Headache, stomach pain', 'Take one capsule daily', 14.00),
(10, 'Loratadine', 'Allergy Relief', 'Tablet', '10mg', 'Used to treat allergy symptoms.', 'Drowsiness, dry mouth', 'Take one tablet daily', 9.50),
(11, 'Metformin', 'Antidiabetic', 'Tablet', '500mg', 'Used to control blood sugar levels in type 2 diabetes.', 'Gastrointestinal upset', 'Take one tablet twice daily', 18.00),
(12, 'Losartan', 'Antihypertensive', 'Tablet', '50mg', 'Used to treat high blood pressure.', 'Dizziness, headache', 'Take one tablet daily', 20.00),
(13, 'Simvastatin', 'Cholesterol-lowering', 'Tablet', '20mg', 'Used to lower cholesterol levels.', 'Muscle pain, digestive issues', 'Take one tablet in the evening', 22.00),
(14, 'Aspirin', 'Pain Reliever', 'Tablet', '81mg', 'Used to reduce the risk of heart attack.', 'Upset stomach, bleeding', 'Take one tablet daily', 3.00),
(15, 'Hydrochlorothiazide', 'Diuretic', 'Tablet', '25mg', 'Used to treat high blood pressure and fluid retention.', 'Dizziness, dehydration', 'Take one tablet daily', 4.50),
(16, 'Clotrimazole', 'Antifungal', 'Cream', '1%', 'Used to treat fungal infections.', 'Skin irritation, redness', 'Apply to affected area twice daily', 10.00),
(17, 'Ranitidine', 'Antacid', 'Tablet', '150mg', 'Used to reduce stomach acid production.', 'Headache, constipation', 'Take one tablet twice daily', 8.00),
(18, 'Albuterol', 'Bronchodilator', 'Inhaler', '90mcg', 'Used to treat asthma and breathing difficulties.', 'Tremors, increased heart rate', 'Inhale 2 puffs as needed', 25.00),
(19, 'Prednisone', 'Corticosteroid', 'Tablet', '10mg', 'Used to reduce inflammation.', 'Weight gain, mood changes', 'Take one tablet daily', 30.00),
(20, 'Warfarin', 'Anticoagulant', 'Tablet', '5mg', 'Used to prevent blood clots.', 'Bleeding, dizziness', 'Take one tablet daily', 15.00),
(21, 'Montelukast', 'Asthma Relief', 'Tablet', '10mg', 'Used to prevent asthma attacks.', 'Headache, abdominal pain', 'Take one tablet daily', 12.00),
(22, 'Levothyroxine', 'Thyroid Hormone', 'Tablet', '50mcg', 'Used to treat hypothyroidism.', 'Insomnia, increased appetite', 'Take one tablet daily on an empty stomach', 18.50),
(23, 'Esomeprazole', 'Antacid', 'Capsule', '40mg', 'Used to treat acid reflux and ulcers.', 'Nausea, dry mouth', 'Take one capsule daily', 19.75),
(24, 'Diazepam', 'Anxiolytic', 'Tablet', '5mg', 'Used to treat anxiety and muscle spasms.', 'Drowsiness, fatigue', 'Take one tablet as needed', 7.00),
(25, 'Furosemide', 'Diuretic', 'Tablet', '40mg', 'Used to treat fluid retention and swelling.', 'Dehydration, dizziness', 'Take one tablet in the morning', 5.50),
(26, 'Panadol', 'pain killer', 'tablet', '100mg', 'jfhakjf', 'fajhf', 'fahkj', 19.00);

-- --------------------------------------------------------

--
-- Table structure for table `medication_transaction`
--

CREATE TABLE `medication_transaction` (
  `Transaction_ID` int(10) NOT NULL,
  `Medication_ID` int(10) UNSIGNED DEFAULT NULL,
  `Quantity` int(5) NOT NULL,
  `Patient_ID` int(10) UNSIGNED NOT NULL,
  `Status` varchar(11) NOT NULL,
  `Hospital_ID` int(10) UNSIGNED NOT NULL,
  `total_price` decimal(7,2) NOT NULL,
  `Transaction_Time` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `medication_transaction`
--

INSERT INTO `medication_transaction` (`Transaction_ID`, `Medication_ID`, `Quantity`, `Patient_ID`, `Status`, `Hospital_ID`, `total_price`, `Transaction_Time`) VALUES
(1, 2, 32, 2, 'Completed', 3, 496.00, '2024-11-20 15:22:35'),
(2, 2, 3, 2, 'Completed', 2, 46.50, '2024-11-22 16:45:00'),
(3, 6, 10, 2, 'Completed', 5, 50.00, '2024-11-22 08:30:10'),
(4, 4, 4, 4, 'Completed', 4, 48.00, '2024-11-23 10:15:50'),
(5, 5, 1, 5, 'Cancelled', 5, 7.25, '2024-11-24 12:50:25'),
(6, 6, 7, 6, 'Completed', 6, 35.00, '2024-11-25 14:05:40'),
(7, 7, 6, 7, 'Completed', 7, 66.00, '2024-11-26 17:55:10'),
(8, 8, 2, 8, 'Pending', 8, 13.00, '2023-11-27 18:20:30'),
(9, 9, 8, 9, 'Completed', 9, 112.00, '2023-11-28 09:40:15'),
(10, 10, 3, 10, 'Completed', 10, 28.50, '2023-11-29 11:25:05'),
(11, 11, 4, 11, 'Completed', 11, 72.00, '2023-11-30 13:10:45'),
(12, 12, 5, 12, 'Completed', 12, 100.00, '2023-12-01 09:55:25'),
(13, 13, 2, 13, 'Pending', 13, 44.00, '2023-12-02 07:40:50'),
(14, 14, 9, 14, 'Completed', 14, 27.00, '2024-12-03 19:30:00'),
(15, 15, 1, 15, 'Completed', 15, 4.50, '2024-06-04 20:05:55'),
(26, 2, 22, 1, 'Completed', 2, 341.00, '2024-12-05 17:34:31'),
(29, 4, 4, 4, 'Completed', 4, 48.00, '2024-12-14 22:37:41'),
(30, 9, 9, 9, 'Completed', 9, 126.00, '2024-12-14 22:46:56'),
(31, 8, 8, 8, 'Completed', 8, 52.00, '2024-12-14 22:47:09'),
(32, 10, 10, 10, 'Completed', 10, 95.00, '2024-12-14 22:52:27'),
(34, 11, 11, 11, 'Completed', 11, 198.00, '2024-12-14 22:54:59'),
(38, 1, 2, 1, 'Completed', 3, 24.00, '2025-01-13 23:24:35'),
(40, 8, 1, 2, 'Completed', 3, 6.50, '2025-01-16 02:36:32');

-- --------------------------------------------------------

--
-- Table structure for table `patient`
--

CREATE TABLE `patient` (
  `Patient_ID` int(10) UNSIGNED NOT NULL,
  `Patient_Name` varchar(50) NOT NULL,
  `Patient_Gender` char(1) NOT NULL,
  `Patient_DOB` date NOT NULL,
  `Patient_Address` varchar(100) NOT NULL,
  `Patient_Height` double NOT NULL,
  `Patient_Weight` double NOT NULL,
  `Patient_TelNo` varchar(14) NOT NULL,
  `Patient_Email` varchar(50) DEFAULT NULL,
  `Medical_History` text DEFAULT NULL,
  `Diagnosed_Symptoms` varchar(1000) DEFAULT NULL,
  `Active_Status` varchar(8) NOT NULL,
  `Patient_Password` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `patient`
--

INSERT INTO `patient` (`Patient_ID`, `Patient_Name`, `Patient_Gender`, `Patient_DOB`, `Patient_Address`, `Patient_Height`, `Patient_Weight`, `Patient_TelNo`, `Patient_Email`, `Medical_History`, `Diagnosed_Symptoms`, `Active_Status`, `Patient_Password`) VALUES
(1, 'IRYN', 'M', '2002-03-21', '8,jalan buaya 14,Taman Puteri Wangsa,8790 Ulu Tiram Johor', 187, 56, '010-6663379', 'iryn@gmail.com', 'Allergy', 'Fever', 'Active', '1f22846cf0a19dc83238298c1f88d71c6f297ed0'),
(2, 'AHMAD NAQIUDDIN BIN MOHAMAD', 'M', '2003-10-05', 'B-G-03, Lorong Saujana Aman 9, Taman Kelmarin', 160.3, 59.35, '010-8654093', 'ahmadnaqiuddinmohamad@example.com', 'No significant history', 'Bacterial infection', 'Active', 'a53a33601b8dd9d06ae9e50f1f30fbe957aba866'),
(3, 'ABU', 'F', '2003-12-21', '3,jalan intan awal 3,91900 ,Bukit Tiram ,Johor', 176, 50, '010-6663379', 'abu15@gmail.com', 'Heatattack', 'Tuberculosis', 'Active', 'b898226e83d28b0dbe26f75a80b7ad6f7d134d8d'),
(4, 'AHMED ABDULKAREEM ABDULLAH MOHAMMED AL-SENWI', 'M', '2002-12-31', 'Jln Bintulu, Taman Bintulu, 14300, Bukit Binatulu', 174.3, 78.9, '017-33456672', 'ahmedabdulkareemabdullahmohammedal-senwi@example.c', 'Diabetes', 'Cough', 'Inactive', '780b39fc1838ec9fd5a6507d62c0fda88b2e9f83'),
(5, 'AMIRUL HAFIZ BIN ANUAR', 'M', '2000-07-12', '2A, Jalan Bintulu, Taman Bintulu, 23450, Sabah', 163.2, 49.9, '017-35678832', 'amirulhafizanuar@example.com', 'No significant history', 'Allergy symptoms', 'Active', '477333017ac7958ab5c0215ec528bde422369527'),
(6, 'AMIRUL HAFIZI BIN ISHAK', 'M', '2002-07-03', '3A, Jalan Mutiara, Taman Mutiara Ria', 175.4, 63.2, '017-8825336', 'amirulhafiziishak@example.com', 'Asthma', 'Wound infection', 'Active', '1f22846cf0a19dc83238298c1f88d71c6f297ed0'),
(7, 'ANG CHA YAN', 'F', '2003-07-08', '108, Jalan Damansara, Taman Damansara', 165.4, 45.5, '012-3344778', 'angchayan@example.com', 'Allergy', 'Inflammation and pain', 'Inactive', 'f71667b55f0b2b907c7bc79ecbb94a0937d0f6d2'),
(8, 'CHE MUHAMMAD AFFIQ BIN CHE MOHD ALWI', 'M', '2003-01-23', '7G-34, Jalan 2/3, PJS72M, 23986 Bukit Payong', 176.2, 63.3, '019-3768823', 'chemuhammadaffiqchemohdalwi@example.com', 'No significant history', 'Constipation', 'Active', '1f22846cf0a19dc83238298c1f88d71c6f297ed0'),
(9, 'CHUAH MING XUAN', 'M', '2003-11-28', 'P-81-76, Jln 94Z, Taman Selatan, 02621 Puching', 169.2, 64.6, '05-8004605', 'chuahmingxuan@example.com', 'No significant history', 'Acid reflux', 'Active', '66d7f53a4a7fae3d93e7986138895727ab414d3e'),
(10, 'Chung Hok Gong', 'M', '2003-06-25', '2, Lorong Wan Kadir 6/47, 23215 Melaka', 162.5, 60.8, '017-3838446', 'chunghokgong@example.com', 'Chronic Migraine', 'Allergy symptoms', 'Active', '4d31653f7e0db8324e33960300adf146a913cdaa'),
(11, 'DANIEL AIMAN HAKIMI BIN MOHD ZAMANI', 'M', '2003-03-18', '37, Jalan Robson, Batu Sg.Buaya, 52778 Tambun', 178.9, 67.4, '015-5444310', 'danielaimanhakimimohdzamani@example.com', 'No significant history', 'Type 2 diabetes', 'Active', '3a823e71995cc36e559c7b9b9de07337c8df66aa'),
(12, 'HO XIN YONG', 'F', '2003-09-23', '2, Lorong Wan Kadir 6/47, 23215 Sg.Petani', 161.4, 46.3, '03-88569242', 'hoxinyong@example.com', 'No significant history', 'High blood pressure', 'Active', 'dcc6a426f15c177d46e342a25afcbf27e53a25d9'),
(13, 'FUAD BIN MOHD RAZALI', 'M', '1980-04-08', '37, Jln Robson, Bt.Buaya, 52778 Tambin', 164.1, 47.2, '05-3066929', 'fuadmohdrazali@example.com', 'High Cholesterol', 'High cholesterol', 'Active', '6ee2bdeabf30bcf51ca80bb6efbe63f9bb72a116'),
(14, 'IRRA SYAHIRAH AMANI BINTI FAKHRUDDIN', 'F', '2002-05-02', '56, Jalan SS9, 59956 Taman U-Thant, Kuala Lumpur', 173.8, 63.9, '016-5722957', 'irrasyahirahamanitifakhruddin@example.com', 'No significant history', 'Heart attack prevention', 'Active', '695860dd65a674d73c57409e58031a0a9798c9ac'),
(15, 'ISAAC RYAN KOIRIN', 'M', '2003-02-16', '1, Jalan 7/12, Batu Melawati, 46889 Semang', 165.8, 60.9, '015-6172561', 'isaacryankoirin@example.com', 'No significant history', 'High blood pressure and fluid retention', 'Active', '6745d0e432da6374b0856dd7cd337471cb13797f'),
(16, 'JASON ONG WAI LEONG', 'M', '2003-11-25', '12, Jalan Aman, Taman Cheras, 43200 Cheras', 168.4, 62.7, '019-2345567', 'jasonong@example.com', 'No significant history', 'Common cold', 'Active', 'ee4d7f1ac5f8a3342d49315cd5e687123cd2a913'),
(17, 'LIM HUI MIN', 'F', '2003-05-14', '27, Lorong Permai 3, 96000 Sibu', 162.5, 53.2, '011-34987564', 'limhuimin@example.com', 'Asthma', 'Breathing difficulties', 'Active', 'ff6e791f0bdc9ef4a43a5623f768ba569a7498b1'),
(18, 'LEE KHAI SHENG', 'M', '2003-12-31', '10, Jalan Putra, Taman Mewah, 81000 Kulai', 175.6, 64.5, '019-5567893', 'leekhaisheng@example.com', 'High blood pressure', 'Chest pain', 'Active', '9973eac8fa99ef4bfc6df657bb6ac789e32c7d6e'),
(19, 'SARAH AMEERA BINTI ALI', 'F', '2001-09-08', '35, Jalan Melati, Taman Ria, 33000 Ipoh', 160.2, 49.7, '016-9983321', 'sarahameera@example.com', 'No significant history', 'Skin rash', 'Active', '43ad89798cd3b9d4efde65e23b8ea4797f8ed219'),
(20, 'MOHD HAZIQ BIN SHAHARUDDIN', 'M', '2003-03-22', '8, Lorong Indah, 42000 Klang', 169.8, 67.3, '012-8745523', 'mohdhaziq@example.com', 'Diabetes', 'Blurred vision', 'Active', 'f1e6c4ad8a273598ef7bd76f9c9e3f75a14c8b2d'),
(21, 'PRIYA NAIR', 'F', '2003-06-18', '2, Jalan Damai, Taman Tanjung, 55000 Kuala Lumpur', 155.5, 51.4, '014-2253345', 'priyanair@example.com', 'Thyroid disorder', 'Fatigue', 'Active', 'e6f493bc17a4ef5c3a53b9d8e7f48c9d5e24ab68'),
(22, 'RAHMAN BIN AZIZ', 'M', '2003-11-10', '45, Jalan Mawar, Taman Sentosa, 85000 Segamat', 172.4, 75.2, '013-9864421', 'rahmanaziz@example.com', 'Heart disease', 'Chest discomfort', 'Active', 'd23f4a78b8e2b5f47fa23d6c7b7d98ea7d16f9e1'),
(23, 'CHONG WEI LING', 'F', '2003-01-15', '18, Jalan Kenanga, Taman Damai, 72000 Seremban', 164.2, 59.8, '017-4462318', 'chongweiling@example.com', 'No significant history', 'Nausea', 'Active', '3e2a6c4e56f874ef2c59d8b9b5f3b6a17c3e2e68'),
(36, 'gojo satoru', 'F', '2002-12-21', '2,jalan keris 34 ,taman yahya awal ', 45, 54, '019-7560221', 'xienxien13@gmail.com', 'headche', 'rain cancer', 'Active', 'b898226e83d28b0dbe26f75a80b7ad6f7d134d8d'),
(37, 'uzumaki naruto', 'F', '2003-12-31', '2,jalan keris 28,taman puteri wangsa', 76, 67, '019-7895678', 'xienxien13@gmail.xom', 'stomache', 'uberculosis', 'Active', 'b898226e83d28b0dbe26f75a80b7ad6f7d134d8d'),
(38, 'hiii', 'F', '2002-03-21', 'ajfkh', 45, 67, '019-7560221', 'afjnjakf', 'afhkjahf', 'jahfk', 'Active', '9bfcb2a9f90b3f20ac0bb95cd03e6ca800c96171');

-- --------------------------------------------------------

--
-- Table structure for table `staff`
--

CREATE TABLE `staff` (
  `Staff_ID` int(10) UNSIGNED NOT NULL,
  `Staff_Name` varchar(100) DEFAULT NULL,
  `Staff_Gender` char(1) NOT NULL,
  `Staff_Address` varchar(100) NOT NULL,
  `Staff_Telno` varchar(15) NOT NULL,
  `Staff_Position` varchar(30) NOT NULL,
  `Staff_Password` varchar(60) NOT NULL,
  `Active_Status` varchar(10) NOT NULL,
  `Hospital_ID` int(10) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `staff`
--

INSERT INTO `staff` (`Staff_ID`, `Staff_Name`, `Staff_Gender`, `Staff_Address`, `Staff_Telno`, `Staff_Position`, `Staff_Password`, `Active_Status`, `Hospital_ID`) VALUES
(1, 'CHAI YI JING', 'M', 'jalan bahaya, ulu tiram johor', '019-8887754', 'Pharmacist', '1f22846cf0a19dc83238298c1f88d71c6f297ed0', 'Active', 7),
(2, 'BOO JIA JUN', 'M', '18 Jalan Melati, Kota Kinabalu', '011-41238846', 'Pharmacist', 'b898226e83d28b0dbe26f75a80b7ad6f7d134d8d', 'Active', 2),
(3, 'NURUL IZZATI BINTI ABDUL RAZAK', 'F', '22 Jalan Melaju, Puchong, Selangor', '018-4076582', 'Pharmacy Assistant', '4d09e8e5de3c6a5acc567a9d64ee9ee96d1a78f9', 'Active', 3),
(4, 'AQILAH', 'F', '3B, Jalan Bukit Bintang, Taman Binatang', '017-4356782', 'Pharmacy Assistant', '780b39fc1838ec9fd5a6507d62c0fda88b2e9f83', 'Active', 4),
(5, 'OOI XIEN XIEN', 'F', '3A, Jalan Bintang, Taman Udang, Bukit Udang', '017-5867363', 'Pharmacy Assistant', 'b898226e83d28b0dbe26f75a80b7ad6f7d134d8d', 'Active', 5),
(6, 'TEE YONG JIAN', 'M', '45, Lorong Sarjana, Taman Sarjana, Pulau Pinang', '012-65478823', 'Pharmacist', 'b898226e83d28b0dbe26f75a80b7ad6f7d134d8d', 'Active', 6),
(7, 'AMANDA VERA YAPP', 'F', 'L22 Bangunan Abdullah, Jln Melaka, Kuala Lumpur', '07-12350543', 'Pharmacist', 'f71667b55f0b2b907c7bc79ecbb94a0937d0f6d2', 'Active', 7),
(8, 'ENGKU AMIR LUTFI BIN ENGKU ZAIN', 'M', '31A Jalan Laksamana 6, Taman Mewah Jaya, Klang', '011-51626857', 'Staff', 'b898226e83d28b0dbe26f75a80b7ad6f7d134d8d', 'Active', 8),
(9, 'HARIS A/L R SURESH', 'M', '764, Jalan Subang 4, Taman Perindustrian', '03-26924094', 'Staff', '66d7f53a4a7fae3d93e7986138895727ab414d3e', 'Inactive', 9),
(10, 'MUHAMMAD AMIERUL BIN CHE WAN MOHD YAZID', 'M', '48, Jalan Mohana Chandran 60V, PJS9, 95380 Lawas', '011-32541158', 'Pharmacy Assistant', '4d31653f7e0db8324e33960300adf146a913cdaa', 'Active', 10),
(11, 'NUR ALIA MUNIRAH BINTI ABD RAHIM', 'F', 'No. L-77-94, Jalan 8, 20711 Chukai, Terengganu', '015-4874820', 'Staff', '3a823e71995cc36e559c7b9b9de07337c8df66aa', 'Active', 11),
(12, 'NURAIN ZAHIDAH BINTI MOHD YUSOF', 'F', 'Lot T-72-63, Lorong 78R, Batu Selamat', '09-4100423', 'Pharmacist', 'dcc6a426f15c177d46e342a25afcbf27e53a25d9', 'Active', 12),
(13, 'SHOMESWARAN A/L MUGUNTHAN', 'M', '78, Jalan Pantai Baharu, PJS49A, 62078 Precinct 16', '07-2995872', 'Pharmacy Assistant', '6ee2bdeabf30bcf51ca80bb6efbe63f9bb72a116', 'Active', 13),
(14, 'AIDA', 'F', '8-6, Jalan Kuala Kangsar 4/65, Bandar Pahlawan', '015-3300466', 'Staff', '695860dd65a674d73c57409e58031a0a9798c9ac', 'Active', 14),
(15, 'TAN LE XIONG', 'M', '7, Jalan 9, PJU33, 76245 Batu Berendam, Melaka', '09-4100423', 'Pharmacist', '6745d0e432da6374b0856dd7cd337471cb13797f', 'Active', 15),
(16, 'LIM PEI YI', 'F', '10A, Jalan Mawar 2, Taman Bahagia, Johor Bahru', '016-4125678', 'Pharmacist', '81f9b2c7b6ec6c9c256534b7b0afc47192e4dcf9', 'Active', 2),
(17, 'AHMAD HAFIZ BIN AZIZAN', 'M', '21, Jalan Sutera, Taman Melawati, Selangor', '013-4446789', 'Pharmacy Assistant', '67e340bfe8da82f7a556b3788888f57b3228d7cf', 'Active', 2),
(18, 'FARAH NABILAH BINTI NORZAID', 'F', '12B, Lorong Seri, Taman Pelangi, Penang', '017-5698123', 'Pharmacist', '8d73f46f9a2c3457a2f9e4d8a9b3c234f7e5ab8c', 'Active', 3),
(19, 'RAJESH A/L KARUPAN', 'M', '31C, Jalan Kenanga, Taman Seri Impian, Ipoh', '012-9998754', 'Staff', '9f6a12a7b9c3d4e8f5a7c9123b67e8d9a5f6e7c9', 'Active', 4),
(20, 'NURUL HUDA BINTI MOHD ZAIN', 'F', '15, Jalan Mawar Merah, Taman Daya, Kota Bharu', '014-3356789', 'Pharmacy Assistant', 'b9c5d8f7e6a4f2d7c3b9a7c5e8d7f9a4e6c5b9d8', 'Active', 5),
(21, 'LEE CHONG WEI', 'M', '42, Jalan SS2/75, Petaling Jaya, Selangor', '019-2345678', 'Pharmacist', 'c8f6d7e4b9a5c3d9e8f7a5c6d8b3a5f7c9e4d8a9', 'Active', 6),
(22, 'AZIZAH BINTI HARUN', 'F', '88, Lorong Mawar Putih, Taman Setia, Alor Setar', '018-2223456', 'Pharmacy Assistant', 'a9d8e7f6c5b4d9e8f7a5b6d9c3e7f8a9d6c5e8f7', 'Active', 7),
(23, 'SYAFIQ BIN HASSAN', 'M', '77, Jalan Dahlia, Taman Bunga Raya, Melaka', '017-9987654', 'Staff', 'e8f7d9c6a5b3e9d8f7a5b4d9c8e7a9d6c5f9e7f8', 'Active', 8),
(24, 'AMY LIM SU HUA', 'F', '56, Lorong Kemboja, Taman Aman, Kuala Lumpur', '016-6654321', 'Pharmacist', 'd9e7f8c6b5d4e9a7c8f6b9d8a7f6e9c5b4a9d7e6', 'Active', 9),
(25, 'MUHAMMAD FIRDAUS BIN AZHAR', 'M', '9B, Jalan Teratai, Taman Permai, Seremban', '015-2344567', 'Pharmacy Assistant', 'f7e6d8b5a9c3d4e8f6b7a5d9c8f7a9d6e4b5c7a8', 'Active', 10);

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
-- Indexes for table `medication_transaction`
--
ALTER TABLE `medication_transaction`
  ADD PRIMARY KEY (`Transaction_ID`),
  ADD KEY `Medication_ID` (`Medication_ID`),
  ADD KEY `Patient_ID` (`Patient_ID`),
  ADD KEY `medication_transaction_ibfk_2` (`Hospital_ID`);

--
-- Indexes for table `patient`
--
ALTER TABLE `patient`
  ADD PRIMARY KEY (`Patient_ID`);

--
-- Indexes for table `staff`
--
ALTER TABLE `staff`
  ADD PRIMARY KEY (`Staff_ID`),
  ADD KEY `staff_ibfk_1` (`Hospital_ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `hospital`
--
ALTER TABLE `hospital`
  MODIFY `Hospital_ID` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=27;

--
-- AUTO_INCREMENT for table `medication`
--
ALTER TABLE `medication`
  MODIFY `Medication_ID` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=27;

--
-- AUTO_INCREMENT for table `medication_transaction`
--
ALTER TABLE `medication_transaction`
  MODIFY `Transaction_ID` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=41;

--
-- AUTO_INCREMENT for table `patient`
--
ALTER TABLE `patient`
  MODIFY `Patient_ID` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=39;

--
-- AUTO_INCREMENT for table `staff`
--
ALTER TABLE `staff`
  MODIFY `Staff_ID` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=32;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `medication_transaction`
--
ALTER TABLE `medication_transaction`
  ADD CONSTRAINT `medication_transaction_ibfk_1` FOREIGN KEY (`Medication_ID`) REFERENCES `medication` (`Medication_ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `medication_transaction_ibfk_2` FOREIGN KEY (`Hospital_ID`) REFERENCES `hospital` (`Hospital_ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `medication_transaction_ibfk_3` FOREIGN KEY (`Patient_ID`) REFERENCES `patient` (`Patient_ID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `staff`
--
ALTER TABLE `staff`
  ADD CONSTRAINT `staff_ibfk_1` FOREIGN KEY (`Hospital_ID`) REFERENCES `hospital` (`Hospital_ID`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
