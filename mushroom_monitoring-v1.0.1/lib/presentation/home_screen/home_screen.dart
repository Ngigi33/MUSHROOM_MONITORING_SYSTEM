import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import '../../core/app_export.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

class HomeScreen extends StatefulWidget {
  const HomeScreen({Key? key})
      : super(
          key: key,
        );
  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  void initState() {
    super.initState();
    readData();
  }

  bool isLoading = true;
  List<String> list = [];
  Future<void> readData() async {
    // Please replace the Database URL
    // which we will get in “Add Realtime Database”
    // step with DatabaseURL

    final url = Uri.https('fir-22fe9-default-rtdb.firebaseio.com', '.json');
    final response = await http.get(url);
    print(response.body);

    // var url =
    //     "mushroom-monitoring-database-default-rtdb.europe-west1.firebasedatabase.app/" ,
    //         "data.json";
    // // Do not remove “data.json”,keep it as it is
    // try {
    //   final response = await http.get(Uri.parse(url));
    //   final extractedData = json.decode(response.body) as Map<String, dynamic>;
    //   if (extractedData == null) {
    //     return;
    //   }
    //   extractedData.forEach((blogId, blogData) {
    //     list.add(blogData["title"]);
    //   });
    //   setState(() {
    //     isLoading = false;
    //     print("...........");
    //   });
    // } catch (error) {
    //   throw error;
    // }
  }

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Scaffold(
        body: Column(
          children: [
            isLoading
                ? CircularProgressIndicator()
                : ListView.builder(
                    padding: const EdgeInsets.all(8),
                    itemCount: list.length,
                    itemBuilder: (BuildContext context, int index) {
                      return Container(
                        child: Center(
                          child: Text(
                            list[index],
                            style: TextStyle(fontSize: 24),
                          ),
                          //
                        ),
                      );
                    },
                  ),
            //   SizedBox(
            //     //width: double.maxFinite,
            //     child: SingleChildScrollView(
            //       child: Padding(
            //         padding: EdgeInsets.only(bottom: 0.v),
            //         child: Column(
            //           crossAxisAlignment: CrossAxisAlignment.start,
            //           children: [
            //             CustomImageView(
            //               imagePath: ImageConstant.imgShape,
            //               height: 157.v,
            //               width: 199.h,
            //             ),
            //             //SizedBox(height: 10.v),
            //             CustomImageView(
            //               imagePath: ImageConstant.imgClipPathGroup,
            //               height: 108.v,
            //               width: 250.h,
            //               alignment: Alignment.center,
            //             )
            //           ],
            //         ),
            //       ),
            //     ),
            //   ),
          ],
        ),
      ),
    );
  }
}
