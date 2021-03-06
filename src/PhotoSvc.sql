USE [master]
GO
/****** Object:  Database [PhotoSvc]    Script Date: 23/03/2014 4:52:16 PM ******/
CREATE DATABASE [PhotoSvc]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'PhotoSvc', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL11.MSSQLSERVER\MSSQL\DATA\PhotoSvc.mdf' , SIZE = 6144KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'PhotoSvc_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL11.MSSQLSERVER\MSSQL\DATA\PhotoSvc_log.ldf' , SIZE = 1792KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
ALTER DATABASE [PhotoSvc] SET COMPATIBILITY_LEVEL = 110
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [PhotoSvc].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [PhotoSvc] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [PhotoSvc] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [PhotoSvc] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [PhotoSvc] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [PhotoSvc] SET ARITHABORT OFF 
GO
ALTER DATABASE [PhotoSvc] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [PhotoSvc] SET AUTO_CREATE_STATISTICS ON 
GO
ALTER DATABASE [PhotoSvc] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [PhotoSvc] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [PhotoSvc] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [PhotoSvc] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [PhotoSvc] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [PhotoSvc] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [PhotoSvc] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [PhotoSvc] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [PhotoSvc] SET  DISABLE_BROKER 
GO
ALTER DATABASE [PhotoSvc] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [PhotoSvc] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [PhotoSvc] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [PhotoSvc] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [PhotoSvc] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [PhotoSvc] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [PhotoSvc] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [PhotoSvc] SET RECOVERY FULL 
GO
ALTER DATABASE [PhotoSvc] SET  MULTI_USER 
GO
ALTER DATABASE [PhotoSvc] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [PhotoSvc] SET DB_CHAINING OFF 
GO
ALTER DATABASE [PhotoSvc] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [PhotoSvc] SET TARGET_RECOVERY_TIME = 0 SECONDS 
GO
EXEC sys.sp_db_vardecimal_storage_format N'PhotoSvc', N'ON'
GO
USE [PhotoSvc]
GO
/****** Object:  Table [dbo].[Photo]    Script Date: 23/03/2014 4:52:16 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Photo](
	[PhotoId] [int] IDENTITY(1,1) NOT NULL,
	[Name] [varchar](256) NOT NULL,
	[Notes] [varchar](1024) NULL,
	[CreatedOn] [smalldatetime] NOT NULL,
	[Data] [image] NOT NULL,
 CONSTRAINT [PK_Photo] PRIMARY KEY CLUSTERED 
(
	[PhotoId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
SET ANSI_PADDING ON

GO
/****** Object:  Index [IX_Photo]    Script Date: 23/03/2014 4:52:16 PM ******/
CREATE NONCLUSTERED INDEX [IX_Photo] ON [dbo].[Photo]
(
	[Name] ASC,
	[CreatedOn] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
ALTER TABLE [dbo].[Photo] ADD  CONSTRAINT [DF_Photo_Notes]  DEFAULT ('') FOR [Notes]
GO
ALTER TABLE [dbo].[Photo] ADD  CONSTRAINT [DF_Photo_CreatedOn]  DEFAULT (getdate()) FOR [CreatedOn]
GO
USE [master]
GO
ALTER DATABASE [PhotoSvc] SET  READ_WRITE 
GO
